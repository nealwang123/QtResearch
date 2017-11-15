/**
 *******************************************************************************
 *                       Continental Confidential
 *                  Copyright (c) Continental AG. 2017
 *
 *      This software is furnished under license and may be used or
 *      copied only in accordance with the terms of such license.
 *******************************************************************************
 * @file    MyCarEntity.h
 * @brief
 *******************************************************************************
 */
#ifndef MYCARENTITY_H
#define MYCARENTITY_H

#include <QPropertyAnimation>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QMesh>

class MyCarEntity : public Qt3DCore::QEntity
{
    Q_OBJECT
    Q_PROPERTY(float position READ getPosition WRITE setPosition NOTIFY positionChanged)
public:
    MyCarEntity(Qt3DCore::QNode* parent = 0);
    virtual ~MyCarEntity();

    void moveTo(const QVector3D& pos);
    void startRun();
    void stopRun();

    float getPosition() const;
    void setPosition(float position);

Q_SIGNALS:
    void positionChanged();

private:
    Qt3DRender::QMesh* m_mesh;
    Qt3DCore::QTransform* m_transform;
    QPropertyAnimation* mRunAnimation;
    float m_position;
};

#endif // MYCARENTITY_H
