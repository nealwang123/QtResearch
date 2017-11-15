/**
 *******************************************************************************
 *                       Continental Confidential
 *                  Copyright (c) Continental AG. 2017
 *
 *      This software is furnished under license and may be used or
 *      copied only in accordance with the terms of such license.
 *******************************************************************************
 * @file    CoubilNodt.cpp
 * @brief
 *******************************************************************************
 */
#include "CoubilNodt.h"

CoubilNodt::CoubilNodt(Qt3DCore::QEntity* rootEntity)
    : mRootEntity(rootEntity)
    , mCuboidTransform(Q_NULLPTR)
    , mRotationX(0)
    , mRotationY(0)
    , mRotationZ(0)
    , mIsDrag(false)
{

    // Cuboid shape data
    mCuboid = new Qt3DExtras::QCuboidMesh;

    // Cuboid shape data
    mCuboidTransform = new Qt3DCore::QTransform;
    mCuboidTransform->setScale(1.0f);
    //    cuboidTransform->setRotation(QQuaternion(0, 0,0,60));
    mCuboidTransform->setRotationZ(60);
    mCuboidTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));

    Qt3DExtras::QPhongMaterial* cuboidMaterial = new Qt3DExtras::QPhongMaterial;
    cuboidMaterial->setDiffuse(QColor(QRgb(0xFFFF00)));

    mCuboidEntity = new Qt3DCore::QEntity(mRootEntity);
    mCuboidEntity->addComponent(mCuboid);
    mCuboidEntity->addComponent(cuboidMaterial);
    mCuboidEntity->addComponent(mCuboidTransform);

    // set animation
    mRotateTransformAnimation = new QPropertyAnimation;
    mRotateTransformAnimation->setTargetObject(this);
    mRotateTransformAnimation->setDuration(2000);
    mRotateTransformAnimation->setPropertyName("angle");
    mRotateTransformAnimation->setProperty("direct", "Z");
    mRotateTransformAnimation->setStartValue(QVariant::fromValue(1));
    mRotateTransformAnimation->setEndValue(QVariant::fromValue(-20));
    mRotateTransformAnimation->setLoopCount(-1);
}

CoubilNodt::~CoubilNodt()
{
    delete mCuboidTransform;
}

void CoubilNodt::rotation(RotationDirection direction, float ros) const
{
    switch (direction)
    {
        case RotationDirection::ForX:
            mCuboidTransform->setRotationX(ros);
            break;
        case RotationDirection::ForY:
            mCuboidTransform->setRotationY(ros);
            break;
        case RotationDirection::ForZ:
            mCuboidTransform->setRotationZ(ros);
            break;
    }
}

void CoubilNodt::moveTo(const QVector3D& pos) const
{
    mCuboidTransform->setTranslation(pos);
}

void CoubilNodt::scalTo(int value)
{
    mCuboidTransform->setScale(value);
}

void CoubilNodt::scalTo(const QVector3D& scale)
{
    mCuboidTransform->setScale3D(scale);
}

void CoubilNodt::setEnable(bool enable)
{
}

const QString& CoubilNodt::getDirect() const
{
    return mDirect;
}

void CoubilNodt::setDirect(const QString& direct)
{
    mDirect = direct;
    emit directChanged();
}

void CoubilNodt::startAnimation()
{
    mRotateTransformAnimation->start();
}

void CoubilNodt::stopAnimation()
{
    mRotateTransformAnimation->stop();
}

bool CoubilNodt::getIsDrag() const
{
    return mIsDrag;
}

void CoubilNodt::setIsDrag(bool isDrag)
{
    mIsDrag = isDrag;
}
