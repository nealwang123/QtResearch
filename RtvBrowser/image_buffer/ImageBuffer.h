#ifndef IMAGEBUFFER_H
#define IMAGEBUFFER_H

#include <QAtomicInt>
#include <QList>
#include <QReadWriteLock>
#include <QThread>

#include "ImageLoaderBase.h"

class ImageBuffer : public QThread
{
    struct ImageData
    {
        int mImageId;
        QImage mImage;
    };

    Q_OBJECT

public:
    ImageBuffer();

    void setImageLoader(ImageLoaderBase* imageLoader);
    void clearImageLoader();

    void setImageReserveCount(int reserveCount);
    int getImageReserveCount() const;

    void enableBuffer(bool enable);
    bool loadImage(int imageId, QImage& image);

Q_SIGNALS:
    void curImageLoaded(int imageId);

protected:
    void run() Q_DECL_OVERRIDE;

private:
    bool loadImageData(int imageId);
    void removeOldImages(const QList<int>& imageIdsReserved);
    void insertImageData(const ImageData& imageData);
    bool hasImageDataNoLock(int imageId) const;

private:
    ImageLoaderBase* mImageLoader;

    int mReserveCount;
    QAtomicInt mCurImageId;

    QReadWriteLock mImageLock;
    QList<ImageData> mImages;

    QAtomicInteger<bool> mEnabled;
};

#endif // IMAGEBUFFER_H
