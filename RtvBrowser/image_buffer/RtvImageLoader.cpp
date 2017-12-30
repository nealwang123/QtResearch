#include "RtvImageLoader.h"

RtvImageLoader::RtvImageLoader()
    : mFile(Q_NULLPTR)
    , mCurImageIndex(0)
{
}

void RtvImageLoader::setImageInfos(QFile* file,
                                   const QVector<RtvImageInfo>& imageInfos)
{
    mFile = file;
    mCurImageIndex = 0;
    mImageInfos = imageInfos;
}

void RtvImageLoader::clear()
{
    mFile = Q_NULLPTR;
    mCurImageIndex = 0;
    mImageInfos.clear();
}

bool RtvImageLoader::setCurImageId(int imageId)
{
    mCurImageIndex = getImageInfoIndex(imageId);
    return (mCurImageIndex >= 0);
}

int RtvImageLoader::moveToPreviousImageId()
{
    if ((mCurImageIndex <= 0) || mImageInfos.isEmpty())
    {
        return -1;
    }

    --mCurImageIndex;
    return mImageInfos[mCurImageIndex].mImageId;
}

int RtvImageLoader::moveToNextImageId()
{
    if (mCurImageIndex >= mImageInfos.size() - 1)
    {
        return -1;
    }

    ++mCurImageIndex;
    return mImageInfos[mCurImageIndex].mImageId;
}

bool RtvImageLoader::loadImage(int imageId, QImage& image)
{
    return (loadImageByIndex(getImageInfoIndex(imageId), image) >= 0);
}

int RtvImageLoader::loadImageByIndex(int imageIndex, QImage& image)
{
    if (mFile == Q_NULLPTR)
    {
        return -1;
    }

    mCurImageIndex = imageIndex;
    if ((mCurImageIndex < 0) || (mCurImageIndex >= mImageInfos.size()))
    {
        return -1;
    }

    const auto& imageInfo = mImageInfos[mCurImageIndex];
    if (mFile->pos() != imageInfo.mOffset)
    {
        mFile->seek(imageInfo.mOffset);
    }

    QByteArray imageData = mFile->read(imageInfo.mLength);
    if (imageData.size() != imageInfo.mLength)
    {
        return -1;
    }

    if (!image.loadFromData(imageData))
    {
        return -1;
    }

    return imageInfo.mImageId;
}

int RtvImageLoader::getImageInfoIndex(int imageId) const
{
    int count = mImageInfos.size();
    for (int i = 0; i < count; ++i)
    {
        if (mImageInfos[i].mImageId == imageId)
        {
            return i;
        }
    }

    return -1;
}
