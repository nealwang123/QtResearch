/**
 *******************************************************************************
 *                       Continental Confidential
 *                  Copyright (c) Continental AG. 2017
 *
 *      This software is furnished under license and may be used or
 *      copied only in accordance with the terms of such license.
 *******************************************************************************
 * @file    RoadEntity.cpp
 * @brief
 *******************************************************************************
 */

#include "RoadEntity.h"
#include <QDebug>

RoadEntity::RoadEntity(QNode* parent)
    : QEntity(parent)
    , m_mesh(Q_NULLPTR)
    , m_transform(Q_NULLPTR)
    , m_material(Q_NULLPTR)

{
    m_mesh = new Qt3DExtras::QPlaneMesh;
    m_mesh->setWidth(glob_roadWidth);
    m_mesh->setHeight(glob_roadLength);

    m_transform = new Qt3DCore::QTransform;
    m_transform->setScale(1);
    m_transform->setRotation(
            QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 0.0f), 0.0f));
    m_transform->setTranslation(QVector3D(0.0f, 0.0f, -glob_roadLength / 2.0));

    m_material = new Qt3DExtras::QPhongMaterial;
    m_material->setDiffuse(QColor(QRgb(0x05ff50)));

    addComponent(m_mesh);
    addComponent(m_material);
    addComponent(m_transform);
}

RoadEntity::~RoadEntity()
{
}
