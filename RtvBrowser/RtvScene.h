/**
 *******************************************************************************
 *                       Continental Confidential
 *                  Copyright (c) Continental AG. 2017
 *
 *      This software is furnished under license and may be used or
 *      copied only in accordance with the terms of such license.
 *******************************************************************************
 * @file    RtvScene.h
 * @brief
 *******************************************************************************
 */
#ifndef RTVSCENE_H
#define RTVSCENE_H

#include <QGraphicsScene>
#include <QImage>

class RtvScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit RtvScene(QObject* parent = Q_NULLPTR);
    virtual ~RtvScene();
    void setSceneRectFromView(const QRect& rect);

    const QImage* getFrameImage() const;
    void setFrameImage(QImage* frameImage);

    const QString& getFrameInformation() const;
    void setFrameInformation(const QString& frameInformation);

    bool getEnableShowDetail() const;
    void setEnableShowDetail(bool enableShowDetail);

private:
    void drawBackground(QPainter* painter, const QRectF& rect);

private:
    QImage* mFrameImage;
    bool mEnableShowDetail;
    QString mFrameInformation;
};

#endif // RTVSCENE_H
