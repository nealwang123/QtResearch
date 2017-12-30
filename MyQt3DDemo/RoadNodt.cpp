/**
 *******************************************************************************
 *                       Continental Confidential
 *                  Copyright (c) Continental AG. 2017
 *
 *      This software is furnished under license and may be used or
 *      copied only in accordance with the terms of such license.
 *******************************************************************************
 * @file    RoadNodt.cpp
 * @brief
 *******************************************************************************
 */
#include "RoadNodt.h"
#include <QDebug>
#include <Qt3DExtras/QTorusMesh>

RoadNodt::RoadNodt(Qt3DCore::QNode* parent)
    : Qt3DCore::QEntity(new Qt3DCore::QEntity(parent))
    , m_mesh(Q_NULLPTR)
    , m_transform(new Qt3DCore::QTransform)
{

    // Plane shape data
    m_mesh = new Qt3DExtras::QPlaneMesh;
    m_mesh->setWidth(3);
    m_mesh->setHeight(200);

    // Plane mesh transform
    m_transform->setScale(1.0f);
    m_transform->setRotation(
            QQuaternion::fromAxisAndAngle(QVector3D(0.1f, 0.0f, 0.0f), 5.0f));
    //    m_transform->setTranslation(QVector3D(0.0f, -4.0f, 0.0f));

    Qt3DExtras::QPhongMaterial* planeMaterial = new Qt3DExtras::QPhongMaterial();
    planeMaterial->setDiffuse(QColor(QRgb(0xa69929)));

    /******************************************************
        Qt3DExtras::QTorusMesh* m_torus = new Qt3DExtras::QTorusMesh();
        m_torus->setRadius(1.0f);
        m_torus->setMinorRadius(0.4f);
        m_torus->setRings(100);
        m_torus->setSlices(20);

        m_transform->setScale(2.0f);
        m_transform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f,
    1.0f, 0.0f), 25.0f));
        m_transform->setTranslation(QVector3D(5.0f, 4.0f, 0.0f));

        Qt3DExtras::QPhongMaterial *torusMaterial = new
    Qt3DExtras::QPhongMaterial();
        torusMaterial->setDiffuse(QColor(QRgb(0xbeb32b)));

    *******************************************************/

    addComponent(m_transform);
    addComponent(m_mesh);
    addComponent(planeMaterial);
}

RoadNodt::~RoadNodt()
{
}

void RoadNodt::moveTo(const QVector3D& pos)
{
    m_transform->setTranslation(pos);
    qDebug() << "move to:" << pos.z();
}
