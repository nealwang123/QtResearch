/**
 *******************************************************************************
 *                       Continental Confidential
 *                  Copyright (c) Continental AG. 2017
 *
 *      This software is furnished under license and may be used or
 *      copied only in accordance with the terms of such license.
 *******************************************************************************
 * @file    MyCarEntity.cpp
 * @brief
 *******************************************************************************
 */
#include "MyCarEntity.h"

MyCarEntity::MyCarEntity(Qt3DCore::QNode* parent)
    : Qt3DCore::QEntity(new Qt3DCore::QEntity(parent))
    , m_mesh(Q_NULLPTR)
    , m_transform(new Qt3DCore::QTransform(this))
    , mRunAnimation(new QPropertyAnimation)
    , m_position(0)
{
    m_mesh = new Qt3DRender::QMesh(this);
    m_mesh->setSource(
            QUrl::fromLocalFile("/home/zxl/Qt5.9.1/Examples/Qt-5.9.1/qt3d/"
                                "exampleresources/assets/chest/Chest.obj"));
    m_transform->setScale(0.05);
    m_transform->setRotationX(45);
    Qt3DExtras::QPhongMaterial* carMaterial = new Qt3DExtras::QPhongMaterial(this);
    carMaterial->setDiffuse(QColor(QRgb(0x00FF00)));

    // set animation
    mRunAnimation->setTargetObject(this);
    mRunAnimation->setDuration(50000);
    mRunAnimation->setPropertyName("position");
    mRunAnimation->setStartValue(QVariant::fromValue(100));
    mRunAnimation->setEndValue(QVariant::fromValue(-100));
    mRunAnimation->setLoopCount(5);

    addComponent(m_mesh);
    addComponent(m_transform);
    addComponent(carMaterial);
}

MyCarEntity::~MyCarEntity()
{
}

void MyCarEntity::moveTo(const QVector3D& pos)
{
    m_transform->setTranslation(pos);
}

void MyCarEntity::startRun()
{
    mRunAnimation->start();
    changeAngle
}

void MyCarEntity::stopRun()
{
    mRunAnimation->stop();
}

float MyCarEntity::getPosition() const
{
    return m_position;
}

void MyCarEntity::setPosition(float position)
{
    m_position = position;
    moveTo(QVector3D(0, -position, position));
    emit positionChanged();
}
