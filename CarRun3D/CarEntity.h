/**
 *******************************************************************************
 *                       Continental Confidential
 *                  Copyright (c) Continental AG. 2017
 *
 *      This software is furnished under license and may be used or
 *      copied only in accordance with the terms of such license.
 *******************************************************************************
 * @file    CarEntity.h
 * @brief
 *******************************************************************************
 */
#ifndef CARENTITY_H
#define CARENTITY_H

#include "DataDefine.h"

#include <QMatrix4x4>
#include <QPropertyAnimation>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QTorusMesh>

class CarEntity : public Qt3DCore::QEntity
{
    Q_OBJECT
    Q_PROPERTY(float angle READ getAngle WRITE setAngle)
public:
    explicit CarEntity(QNode* parent = nullptr);
    virtual ~CarEntity();

    void startRun(bool ok);
    void stopRun();

    float getAngle() const;
    void setAngle(float angle);

    Qt3DCore::QTransform* getTransform() const;

Q_SIGNALS:
    void angleChanged(float angle);
    void posionChanged();

private:
    Qt3DExtras::QTorusMesh* m_mesh;
    Qt3DCore::QTransform* m_transform;
    Qt3DExtras::QPhongMaterial* m_material;

    QPropertyAnimation* m_rotateTransfromAnimation;
    float m_angle;
    QMatrix4x4 m_matrix;
};

#endif // CARENTITY_H
