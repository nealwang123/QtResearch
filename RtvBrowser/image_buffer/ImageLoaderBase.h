#ifndef IMAGELOADERBASE_H
#define IMAGELOADERBASE_H

#include <QImage>

class ImageLoaderBase
{
public:
    virtual ~ImageLoaderBase() = default;

    virtual void clear() = 0;
    virtual bool setCurImageId(int imageId) = 0;
    virtual int moveToPreviousImageId() = 0;
    virtual int moveToNextImageId() = 0;

    virtual bool loadImage(int imageId, QImage& image) = 0;
};

#endif // IMAGELOADERBASE_H
