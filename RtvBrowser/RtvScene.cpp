/**
 *******************************************************************************
 *                       Continental Confidential
 *                  Copyright (c) Continental AG. 2017
 *
 *      This software is furnished under license and may be used or
 *      copied only in accordance with the terms of such license.
 *******************************************************************************
 * @file    RtvScene.cpp
 * @brief
 *******************************************************************************
 */
#include "RtvScene.h"

#include <QDebug>
#include <QPainter>

RtvScene::RtvScene(QObject* parent)
    : QGraphicsScene(parent)
    , mFrameImage(Q_NULLPTR)
    , mEnableShowDetail(false)
{
    setBackgroundBrush(Qt::black);
    setBspTreeDepth(1);
}

RtvScene::~RtvScene()
{
}

void RtvScene::setSceneRectFromView(const QRect& rect)
{
    setSceneRect(rect);
    update(rect);
}

void RtvScene::drawBackground(QPainter* painter, const QRectF& rect)
{
    painter->beginNativePainting();
    if (mFrameImage == Q_NULLPTR)
    {
        painter->fillRect(rect, QColor("#FFFFFF"));
    }
    else
    {
        painter->drawImage(rect, *mFrameImage);
    }
    if (mEnableShowDetail && !mFrameInformation.isEmpty())
    {
        QRect attrRect(20, 20, 200, 80);
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);

        QBrush brush(QColor(48, 48, 48, 96));
        painter->setBrush(brush);
        painter->setPen(QPen(brush, 0.5, Qt::SolidLine));
        painter->drawRoundedRect(attrRect.marginsAdded(QMargins(10, 10, 0, 0)),
                                 5, 5);
        painter->restore();

        QFont font;
        painter->save();
        font.setPixelSize(11);
        painter->setFont(font);
        painter->setPen(Qt::white);
        painter->drawText(attrRect, mFrameInformation);
        painter->restore();
    }
    painter->endNativePainting();
}

bool RtvScene::getEnableShowDetail() const
{
    return mEnableShowDetail;
}

void RtvScene::setEnableShowDetail(bool enableShowDetail)
{
    mEnableShowDetail = enableShowDetail;
}

const QString& RtvScene::getFrameInformation() const
{
    return mFrameInformation;
}

void RtvScene::setFrameInformation(const QString& frameInformation)
{
    mFrameInformation = frameInformation;
}

const QImage* RtvScene::getFrameImage() const
{
    return mFrameImage;
}

void RtvScene::setFrameImage(QImage* frameImage)
{
    mFrameImage = frameImage;
    update();
}
