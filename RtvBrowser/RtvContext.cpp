/**
 *******************************************************************************
 *                       Continental Confidential
 *                  Copyright (c) Continental AG. 2017
 *
 *      This software is furnished under license and may be used or
 *      copied only in accordance with the terms of such license.
 *******************************************************************************
 * @file    RtvContext.cpp
 * @brief
 *******************************************************************************
 */
#include "RtvContext.h"

#include <QDebug>
#include <QFile>
#include <QPixmap>

const int RtvContext::mHeadByteCount = 72;
const double RtvContext::mNdsCoefficient = 0.000000084;

RtvContext::RtvContext()
    : mIsReady(false)
    , mTagByteCount(36)
{
}

RtvContext::~RtvContext()
{
    uninitialize();
}

bool RtvContext::setHeadData(const QByteArray& bytes)
{
    if (bytes.isEmpty())
    {
        return false;
    }
    mHeadStruct.magic_code = bytes.left(11);
    mHeadStruct.flags = bytes[11];
    mHeadStruct.version = bytes.mid(12, 2);
    mHeadStruct.device_id = bytes.mid(14, 24);
    mHeadStruct.start_time = bytesToInt(bytes.mid(38, 8));
    mHeadStruct.start_position[0] = bytesToInt(bytes.mid(46, 4));
    mHeadStruct.start_position[1] = bytesToInt(bytes.mid(50, 4));
    mHeadStruct.start_position[2] = bytesToInt(bytes.mid(54, 4));
    mHeadStruct.frames_count = bytesToInt(bytes.mid(58, 2));
    mHeadStruct.frame_max = bytesToInt(bytes.mid(60, 2));
    mHeadStruct.video_resolution[0] = bytesToInt(bytes.mid(62, 2));
    mHeadStruct.video_resolution[1] = bytesToInt(bytes.mid(64, 2));
    mHeadStruct.frame_format = bytes[66];
    mHeadStruct.frame_codec = bytes[67];
    mHeadStruct.tagging_flags = bytesToInt(bytes.mid(68, 4));

    if (static_cast<int>(mHeadStruct.version[1]) == 0x04)
    {
        mTagByteCount = 145;
    }
    return true;
}

TagStruct RtvContext::getTagData(const QByteArray& bytes)
{
    TagStruct tagStruct;
    tagStruct.time_flag = bytesToInt(bytes.left(4));
    tagStruct.data_offset = bytesToInt(bytes.mid(4, 8));
    tagStruct.data_length = bytesToInt(bytes.mid(12, 4));
    tagStruct.relative_position[0] = bytesToInt(bytes.mid(16, 4));
    tagStruct.relative_position[1] = bytesToInt(bytes.mid(20, 4));
    tagStruct.relative_position[2] = bytesToInt(bytes.mid(24, 4));
    tagStruct.relative_distance = bytesToInt(bytes.mid(28, 4));
    tagStruct.speed = bytesToInt(bytes.mid(32, 2));
    tagStruct.direction = bytesToInt(bytes.mid(34, 2));
    return tagStruct;
}

bool RtvContext::initialize(const QString& rtvFilePath)
{
    mIsReady = false;
    mRtvFilePath = rtvFilePath;
    mRtvFile.setFileName(mRtvFilePath);
    QFile& rtvFile = mRtvFile;

    if (!rtvFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "openfile rtv fail!" << rtvFile.fileName();
        return false;
    }

    rtvFile.seek(0);

    if (!setHeadData(rtvFile.read(mHeadByteCount)))
    {
        rtvFile.close();
        return false;
    }

    QVector<RtvImageInfo> imageInfos;

    cleanTags();
    mTags.resize(mHeadStruct.frames_count);
    rtvFile.seek(mHeadByteCount);
    for (int i = 0; i < static_cast<int>(mHeadStruct.frames_count); ++i)
    {
        mTags[i] = getTagData(rtvFile.read(mTagByteCount));

        RtvImageInfo imageInfo;
        imageInfo.mImageId = i;
        imageInfo.mOffset = mTags[i].data_offset;
        imageInfo.mLength = mTags[i].data_length;
        imageInfos.append(imageInfo);
    }

    // get frame from rtv file
    //    cleanFrmaes();
    //    for (int i = 0; i < mTags.size(); ++i)
    //    {
    //        const TagStruct& tag = mTags[i];
    //        if (tag.data_offset < 0)
    //        {
    //            qDebug() << "frame data offset  < 0";
    //            continue;
    //        }
    //        if (!rtvFile.seek(tag.data_offset))
    //        {
    //            qDebug() << "rtv file seek fail!" << tag.data_offset <<
    //            tag.data_length;
    //            break;
    //        }

    ////        char* imgData = new char[tag.data_length];
    ////        rtvFile.read(imgData, tag.data_length);
    ////        QImage* image = new QImage();
    ////        image->loadFromData(static_cast<uchar*>((void*)(imgData)),
    ///tag.data_length);
    ////        delete[] imgData;
    ////        imgData = Q_NULLPTR;
    //        QImage* image = new QImage;
    //        image->loadFromData(rtvFile.read(tag.data_length));

    //        if (image != Q_NULLPTR)
    //        {
    //            mFrames.append(image);
    //        }
    //    }

    // rtvFile.close();
    mLoader.setImageInfos(&mRtvFile, imageInfos);
    mBuffer.setImageLoader(&mLoader);
    QImage image;
    mBuffer.setImageReserveCount(10);
    mBuffer.loadImage(0, image);

    mIsReady = true;

    return true;
}

void RtvContext::cleanTags()
{
    mTags.clear();
}

void RtvContext::cleanFrmaes()
{
    for (auto* item : mFrames)
    {
        if (item != Q_NULLPTR)
        {
            delete item;
            item = Q_NULLPTR;
        }
    }

    mFrames.clear();
}

double RtvContext::getNdsCoefficient()
{
    return mNdsCoefficient;
}

const Head& RtvContext::getHeadStruct() const
{
    return mHeadStruct;
}

TagStruct RtvContext::getTagInfo(int index) const
{
    if (index < mTags.count())
    {
        return mTags[index];
    }

    return TagStruct();
}

void RtvContext::uninitialize()
{
    mIsReady = false;
    mBuffer.clearImageLoader();

    cleanFrmaes();
    cleanTags();
    mRtvFile.close();
    mHeadStruct = Head();
}

ImageBuffer& RtvContext::getImageBuffer()
{
    return mBuffer;
}

bool RtvContext::isReady() const
{
    return mIsReady;
}

bool RtvContext::getFrame(int frameIndex, QImage& image)
{
    return mBuffer.loadImage(frameIndex, image);
}

QImage* RtvContext::getFrame(int frameIndex)
{
    if (frameIndex < mFrames.count())
    {
        return mFrames[frameIndex];
    }

    return Q_NULLPTR;
}

qint64 bytesToInt(QByteArray bytes)
{
    qint64 right = 1;
    const qint64 power = 256;
    qint64 addr = 0;
    for (int i = 0; i < bytes.size(); ++i)
    {
        addr += (unsigned char)(bytes[i]) * right;
        right *= power;
    }
    return addr;
}
