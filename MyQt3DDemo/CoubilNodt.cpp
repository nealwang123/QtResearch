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
    mCuboidTransform->setTranslation(QVector3D(5.0f, -4.0f, 0.0f));

    Qt3DExtras::QPhongMaterial* cuboidMaterial = new Qt3DExtras::QPhongMaterial;
    cuboidMaterial->setDiffuse(QColor(QRgb(0x00ff00)));

    mCuboidEntity = new Qt3DCore::QEntity(mRootEntity);
    mCuboidEntity->addComponent(mCuboid);
    mCuboidEntity->addComponent(cuboidMaterial);
    mCuboidEntity->addComponent(mCuboidTransform);
}

CoubilNodt::~CoubilNodt()
{
    delete mCuboidTransform;
}

void CoubilNodt::setAngle(float angle)
{
    if (!mIsDrag)
    {
        m_angle = angle;
        if (mDirect == "X")
        {
            rotation(RotationDirection::ForX, angle);
        }
        else if (mDirect == "Y")
        {
            rotation(RotationDirection::ForY, angle);
        }
        else if (mDirect == "Z")
        {
            rotation(RotationDirection::ForZ, angle);
        }
    }
    emit angleChanged();
}

float CoubilNodt::angle() const
{
    return m_angle;
}

void CoubilNodt::rotation(RotationDirection direction, float ros)
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

bool CoubilNodt::getIsDrag() const
{
    return mIsDrag;
}

void CoubilNodt::setIsDrag(bool isDrag)
{
    mIsDrag = isDrag;
}
