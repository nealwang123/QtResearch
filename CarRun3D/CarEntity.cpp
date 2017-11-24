/**
 *******************************************************************************
 *                       Continental Confidential
 *                  Copyright (c) Continental AG. 2017
 *
 *      This software is furnished under license and may be used or
 *      copied only in accordance with the terms of such license.
 *******************************************************************************
 * @file    CarEntity.cpp
 * @brief
 *******************************************************************************
 */

#include "CarEntity.h"
#include <QDebug>

CarEntity::CarEntity(Qt3DCore::QNode* parent)
    : QEntity(parent)
    , m_mesh(Q_NULLPTR)
    , m_transform(Q_NULLPTR)
    , m_material(Q_NULLPTR)
    , m_rotateTransfromAnimation(Q_NULLPTR)
{
    m_mesh = new Qt3DExtras::QTorusMesh;
    m_mesh->setRadius(1.0f);
    m_mesh->setMinorRadius(0.3);
    m_mesh->setRings(10);
    m_mesh->setSlices(20);

    m_transform = new Qt3DCore::QTransform;
    m_transform->setScale(1);
    m_transform->setRotation(
            QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 90.0f));
    m_transform->setTranslation(QVector3D(0.0f, 1.3f, 0.0f));

    m_material = new Qt3DExtras::QPhongMaterial;
    m_material->setDiffuse(QColor(QRgb(0xbeb32b)));

    addComponent(m_mesh);
    addComponent(m_material);
    addComponent(m_transform);

    // set animation
    m_rotateTransfromAnimation = new QPropertyAnimation;
    m_rotateTransfromAnimation->setTargetObject(this);
    m_rotateTransfromAnimation->setDuration(1000);
    m_rotateTransfromAnimation->setPropertyName("angle");
    m_rotateTransfromAnimation->setStartValue(QVariant::fromValue(360));
    m_rotateTransfromAnimation->setEndValue(QVariant::fromValue(0));
    m_rotateTransfromAnimation->setLoopCount(-1);
}

CarEntity::~CarEntity()
{
}

void CarEntity::startRun(bool ok)
{
    if (ok)
    {
        m_rotateTransfromAnimation->start();
    }
    else
    {
        m_rotateTransfromAnimation->pause();
    }
}

void CarEntity::stopRun()
{
    m_rotateTransfromAnimation->stop();
}

float CarEntity::getAngle() const
{
    return m_angle;
}

void CarEntity::setAngle(float angle)
{
    m_angle = angle;
    //    m_transform->setRotationZ(angle);
    //    m_transform->setTranslation(QVector3D(0.0f, 1.3f, 0.0f));

    QVector3D pos = m_transform->translation();
    if (pos.z() < -glob_roadLength)
    {
        pos.setZ(0.01);
    }
    m_matrix.setToIdentity();
    m_matrix.translate(pos.x(), pos.y(), pos.z() - glob_carSpeed);
    m_matrix.rotate(90, QVector3D(0, 1, 0));
    m_matrix.rotate(angle, QVector3D(0.0f, 0.0f, 1.0f));
    m_transform->setMatrix(m_matrix);
    emit posionChanged();
}

Qt3DCore::QTransform* CarEntity::getTransform() const
{
    return m_transform;
}
