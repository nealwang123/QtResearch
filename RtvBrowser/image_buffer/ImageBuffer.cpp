#include "ImageBuffer.h"

ImageBuffer::ImageBuffer()
    : mImageLoader(Q_NULLPTR)
    , mReserveCount(100)
    , mCurImageId(0)
    , mEnabled(true)
{
}

void ImageBuffer::setImageLoader(ImageLoaderBase* imageLoader)
{
    mImageLoader = imageLoader;
}

void ImageBuffer::clearImageLoader()
{
    if (isRunning())
    {
        quit();
        wait();
    }

    if (mImageLoader != Q_NULLPTR)
    {
        mImageLoader->clear();
        mImageLoader = Q_NULLPTR;
    }

    mCurImageId = 0;

    {
        QWriteLocker locker(&mImageLock);
        mImages.clear();
    }
}

void ImageBuffer::setImageReserveCount(int reserveCount)
{
    mReserveCount = reserveCount;
}

int ImageBuffer::getImageReserveCount() const
{
    return mReserveCount;
}

void ImageBuffer::enableBuffer(bool enable)
{
    mEnabled = enable;
}

bool ImageBuffer::loadImage(int imageId, QImage& image)
{
    if (mImageLoader == Q_NULLPTR)
    {
        return false;
    }

    mCurImageId = imageId;

    int count;
    int index;
    bool find;
    {
        QReadLocker locker(&mImageLock);
        count = mImages.size();
        if (count <= 0)
        {
            start();
            return false;
        }

        index = -1;
        find = false;
        for (const auto& iter : mImages)
        {
            ++index;
            if (iter.mImageId == imageId)
            {
                image = iter.mImage;
                find = true;
                break;
            }
        }
    }

    if (!find || (index < mReserveCount) || (count - index < mReserveCount))
    {
        start();
    }

    return find;
}

void ImageBuffer::run()
{
    if (!mEnabled)
    {
        return;
    }

    if (mImageLoader == Q_NULLPTR)
    {
        return;
    }

    QList<int> imageIdsReserved;
    QList<int> imageIdsNew;
    bool findCurImage;
    int curImageId;
    {
        QReadLocker locker(&mImageLock);
        int imageId = mCurImageId;
        curImageId = imageId;
        mImageLoader->setCurImageId(imageId);
        imageIdsReserved.prepend(imageId);
        for (int i = 0; i < mReserveCount; ++i)
        {
            imageId = mImageLoader->moveToPreviousImageId();
            if (imageId < 0)
            {
                break;
            }

            imageIdsReserved.prepend(imageId);
            if (!hasImageDataNoLock(imageId))
            {
                imageIdsNew.prepend(imageId);
            }
        }

        imageId = mCurImageId;
        mImageLoader->setCurImageId(imageId);
        for (int i = 0; i < mReserveCount; ++i)
        {
            imageId = mImageLoader->moveToNextImageId();
            if (imageId < 0)
            {
                break;
            }

            imageIdsReserved.append(imageId);
            if (!hasImageDataNoLock(imageId))
            {
                imageIdsNew.append(imageId);
            }
        }

        findCurImage = hasImageDataNoLock(curImageId);
    }

    removeOldImages(imageIdsReserved);

    if (!findCurImage)
    {
        loadImageData(curImageId);
        emit curImageLoaded(curImageId);
    }

    for (const auto& imageId : imageIdsNew)
    {
        loadImageData(imageId);
    }
}

bool ImageBuffer::loadImageData(int imageId)
{
    if (mImageLoader == Q_NULLPTR)
    {
        return false;
    }

    ImageData imageData;
    imageData.mImageId = imageId;
    if (!mImageLoader->loadImage(imageId, imageData.mImage))
    {
        return false;
    }

    insertImageData(imageData);
    return true;
}

void ImageBuffer::removeOldImages(const QList<int>& imageIdsReserved)
{
    QWriteLocker locker(&mImageLock);
    bool find;
    for (auto iter = mImages.begin(); iter != mImages.end();)
    {
        find = false;
        for (const auto& imageId : imageIdsReserved)
        {
            if (iter->mImageId == imageId)
            {
                find = true;
                break;
            }
        }

        if (find)
        {
            ++iter;
        }
        else
        {
            iter = mImages.erase(iter);
        }
    }
}

void ImageBuffer::insertImageData(const ImageBuffer::ImageData& imageData)
{
    QWriteLocker locker(&mImageLock);
    for (auto iter = mImages.begin(); iter != mImages.end(); ++iter)
    {
        if (imageData.mImageId < iter->mImageId)
        {
            mImages.insert(iter, imageData);
            return;
        }

        if (iter->mImageId == imageData.mImageId)
        {
            iter->mImage = imageData.mImage;
            return;
        }
    }

    mImages.append(imageData);
}

bool ImageBuffer::hasImageDataNoLock(int imageId) const
{
    for (const auto& iter : mImages)
    {
        if (iter.mImageId == imageId)
        {
            return true;
        }
    }

    return false;
}
