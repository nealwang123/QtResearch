/**
 *******************************************************************************
 *                       Continental Confidential
 *                  Copyright (c) Continental AG. 2017
 *
 *      This software is furnished under license and may be used or
 *      copied only in accordance with the terms of such license.
 *******************************************************************************
 * @file    RtvView.h
 * @brief
 *******************************************************************************
 */
#ifndef RTVVIEW_H
#define RTVVIEW_H

#include "RtvContext.h"
#include "RtvScene.h"

#include <QAtomicInt>
#include <QGraphicsView>
#include <QTimer>

class RtvView : public QGraphicsView
{
    enum PlayState
    {
        Playing,
        Paused,
        Stopped
    };

    Q_OBJECT
public:
    explicit RtvView(QWidget* parent = Q_NULLPTR);
    virtual ~RtvView();

    bool initalize(const QString& rtvPath);
    void uninitalize();

    void play();
    void pause();
    void stop();
    void goTo(int frameIndex);
    int getCurFrameIndex() const;

    int getUpdateRate() const;
    void setUpdateRate(int updateRate);
    const Head& getRtvInfo() const;
    bool isPlay() const;
    bool isPaused() const;
    bool isStopped() const;
    bool isReady() const;
    void setEnableShowDetail(bool show);

Q_SIGNALS:
    void currentFrameChanged(int index);
    void playFinished();

public Q_SLOTS:
    void updateFrame();
    void onCurImageLoaded(int imageId);

private:
    void resizeEvent(QResizeEvent* event);

private:
    QImage mCurImage;
    RtvScene* mScene;
    RtvContext mRtvContext;
    int mCurrentIndex;
    int mUpdateRate;
    QAtomicInt mState;
    QTimer* mUpdateTimer;
};

#endif // RTVVIEW_H
