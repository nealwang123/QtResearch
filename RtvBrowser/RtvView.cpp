/**
 *******************************************************************************
 *                       Continental Confidential
 *                  Copyright (c) Continental AG. 2017
 *
 *      This software is furnished under license and may be used or
 *      copied only in accordance with the terms of such license.
 *******************************************************************************
 * @file    RtvView.cpp
 * @brief
 *******************************************************************************
 */
#include "RtvView.h"
#include <QDateTime>
#include <QDebug>
#include <QGLWidget>
#include <QResizeEvent>
#include <QTimeZone>

RtvView::RtvView(QWidget* parent)
    : QGraphicsView(parent)
    , mScene(new RtvScene(this))
    , mCurrentIndex(0)
    , mUpdateRate(33)
    , mState(PlayState::Stopped)
    , mUpdateTimer(new QTimer(this))
{
    setFrameShadow(QFrame::Plain);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setOptimizationFlags(QGraphicsView::DontSavePainterState);
    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setViewport(new QGLWidget(QGLFormat(QGL::DoubleBuffer)));
    setScene(mScene);
    mScene->setSceneRect(0, 0, 1280, 800);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);

    mUpdateTimer->setInterval(mUpdateRate);

    connect(mUpdateTimer, &QTimer::timeout, this, &RtvView::updateFrame);
    connect(&mRtvContext.getImageBuffer(), &ImageBuffer::curImageLoaded, this,
            &RtvView::onCurImageLoaded);
}

RtvView::~RtvView()
{
    uninitalize();
}

bool RtvView::initalize(const QString& rtvPath)
{
    uninitalize();

    if (!mRtvContext.initialize(rtvPath))
    {
        return false;
    }

    goTo(0);
    return true;
}

void RtvView::uninitalize()
{
    mCurrentIndex = 0;
    mRtvContext.uninitialize();
}

void RtvView::play()
{
    if (!mRtvContext.isReady())
    {
        return;
    }

    if (mUpdateTimer->isActive())
    {
        return;
    }

    mState = PlayState::Playing;
    mUpdateTimer->start();
}

void RtvView::pause()
{
    mState = PlayState::Paused;
    mUpdateTimer->stop();
}

void RtvView::stop()
{
    mState = PlayState::Stopped;
    mUpdateTimer->stop();
    goTo(0);
}

void RtvView::goTo(int frameIndex)
{
    if (frameIndex < 0)
    {
        mCurrentIndex = 0;
    }
    else if (frameIndex
             >= static_cast<int>(mRtvContext.getHeadStruct().frames_count))
    {
        mCurrentIndex = mRtvContext.getHeadStruct().frames_count - 1;
    }
    else
    {
        mCurrentIndex = frameIndex;
    }

    if (!isPlay())
    {
        mRtvContext.getFrame(mCurrentIndex, mCurImage);
        mScene->setFrameImage(&mCurImage);
    }
}

int RtvView::getCurFrameIndex() const
{
    return mCurrentIndex;
}

void RtvView::resizeEvent(QResizeEvent* event)
{
    if (mScene != Q_NULLPTR)
    {
        QRect rect = QRect(QPoint(0, 0), event->size());
        mScene->setSceneRect(rect);
    }
    event->accept();
}

int RtvView::getUpdateRate() const
{
    return mUpdateRate;
}

void RtvView::setUpdateRate(int updateRate)
{
    mUpdateRate = updateRate;
}

const Head& RtvView::getRtvInfo() const
{
    return mRtvContext.getHeadStruct();
}

bool RtvView::isPlay() const
{
    return (mState == PlayState::Playing);
}

bool RtvView::isPaused() const
{
    return (mState == PlayState::Paused);
}

bool RtvView::isStopped() const
{
    return (mState == PlayState::Stopped);
}

bool RtvView::isReady() const
{
    return mRtvContext.isReady();
}

void RtvView::setEnableShowDetail(bool show)
{
    mScene->setEnableShowDetail(show);
}

void RtvView::updateFrame()
{
    mCurrentIndex += 1;
    const Head& rtvHead = mRtvContext.getHeadStruct();
    const TagStruct& rtvTag = mRtvContext.getTagInfo(mCurrentIndex);
    if (mCurrentIndex >= static_cast<int>(rtvHead.frames_count))
    {
        mUpdateTimer->stop();
        mCurrentIndex = 0;
        mState = PlayState::Stopped;
        emit playFinished();
        return;
    }

    if (mRtvContext.getFrame(mCurrentIndex, mCurImage))
    {
        mScene->setFrameImage(&mCurImage);
    }
    else
    {
        qDebug() << "Image not found: " << mCurrentIndex;
    }

    QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(rtvHead.start_time);
    mScene->setFrameInformation(
            QString("Frame : %1 / %2\nStart Time : %3\nStart Position : "
                    "%4\nFrame "
                    "Times : %5\nFrame Position : %6")
                    .arg(mCurrentIndex)
                    .arg(rtvHead.frames_count)
                    .arg(dateTime.toString("yyyy/MM/dd hh:mm:ss"))
                    .arg(QString("%1, %2")
                                 .arg(mRtvContext.getNdsCoefficient()
                                      * rtvHead.start_position[0])
                                 .arg(mRtvContext.getNdsCoefficient()
                                      * rtvHead.start_position[1]))
                    .arg(dateTime.addMSecs(rtvTag.time_flag)
                                 .toString("yyyy/MM/dd hh:mm:ss"))
                    .arg(QString("%1, %2")
                                 .arg(mRtvContext.getNdsCoefficient()
                                      * (rtvHead.start_position[0]
                                         + rtvTag.relative_position[0]))
                                 .arg(mRtvContext.getNdsCoefficient()
                                      * (rtvHead.start_position[0]
                                         + rtvTag.relative_position[1]))));
    emit currentFrameChanged(mCurrentIndex);
}

void RtvView::onCurImageLoaded(int imageId)
{
    mRtvContext.getFrame(imageId, mCurImage);
    mScene->setFrameImage(&mCurImage);
}
