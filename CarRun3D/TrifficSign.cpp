/**
 *******************************************************************************
 *                       Continental Confidential
 *                  Copyright (c) Continental AG. 2017
 *
 *      This software is furnished under license and may be used or
 *      copied only in accordance with the terms of such license.
 *******************************************************************************
 * @file    TrifficSign.cpp
 * @brief
 *******************************************************************************
 */
#include "TrifficSign.h"

TrifficSign::TrifficSign(Qt3DCore::QNode* parent)
    : QEntity(parent)
    , m_mesh(Q_NULLPTR)
    , m_transform(Q_NULLPTR)
    , m_material(Q_NULLPTR)
{
    m_mesh = new Qt3DExtras::QCuboidMesh;
    m_mesh->setShareable(true);
    m_mesh->setXExtent(0.5);
    m_mesh->setYExtent(2);
    m_mesh->setZExtent(0.5);

    m_transform = new Qt3DCore::QTransform;
    m_transform->setScale(1);
    m_transform->setRotation(
            QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 0.0f));
    m_transform->setTranslation(QVector3D(-glob_roadWidth / 2, 1.3f, 0.0f));

    m_material = new Qt3DExtras::QPhongMaterial;
    m_material->setDiffuse(QColor(QRgb(0xFFFFFF)));

    addComponent(m_mesh);
    addComponent(m_material);
    addComponent(m_transform);
}

TrifficSign::~TrifficSign()
{
    delete m_mesh;
    delete m_material;
    delete m_transform;
}

void TrifficSign::setPosition(const QVector3D& pos)
{
    m_transform->setTranslation(pos);
}
