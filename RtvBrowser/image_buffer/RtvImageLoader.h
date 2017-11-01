#ifndef RTVIMAGELOADER_H
#define RTVIMAGELOADER_H

#include <QFile>
#include <QVector>

#include "ImageLoaderBase.h"

struct RtvImageInfo
{
    int mImageId;
    qint64 mOffset;
    qint64 mLength;
};

class RtvImageLoader : public ImageLoaderBase
{
public:
    RtvImageLoader();

    void setImageInfos(QFile* file, const QVector<RtvImageInfo>& imageInfos);

    void clear() Q_DECL_OVERRIDE;
    bool setCurImageId(int imageId) Q_DECL_OVERRIDE;
    int moveToPreviousImageId() Q_DECL_OVERRIDE;
    int moveToNextImageId() Q_DECL_OVERRIDE;

    bool loadImage(int imageId, QImage& image) Q_DECL_OVERRIDE;

private:
    int loadImageByIndex(int imageIndex, QImage& image);
    int getImageInfoIndex(int imageId) const;

private:
    QFile* mFile;
    int mCurImageIndex;
    QVector<RtvImageInfo> mImageInfos;
};

#endif // RTVIMAGELOADER_H
