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
#include <QFont>

TrifficSign::TrifficSign(const QString& symble, Qt3DCore::QNode* parent)
    : QEntity(parent)
    , m_mesh(Q_NULLPTR)
    , m_transform(Q_NULLPTR)
    , m_material(Q_NULLPTR)
    , m_textureMaterial(Q_NULLPTR)
    , m_symble(Q_NULLPTR)
    , m_symbleTransform(Q_NULLPTR)
    , m_symbleTextMesh(Q_NULLPTR)
    , m_symbleTextMaterial(Q_NULLPTR)
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

    // add texture
    Qt3DRender::QTextureImage* img = new Qt3DRender::QTextureImage;
    img->setSource(QUrl("://pic/q.png"));
    m_textureMaterial = new Qt3DExtras::QTextureMaterial;
    //    m_textureMaterial->setTexture();

    createSymble(symble);

    addComponent(m_mesh);
    addComponent(m_material);
    addComponent(m_transform);
}

TrifficSign::~TrifficSign()
{
    delete m_mesh;
    delete m_material;
    delete m_textureMaterial;
    delete m_transform;
    delete m_symble;
    delete m_symbleTransform;
    delete m_symbleTextMesh;
    delete m_symbleTextMaterial;
}

void TrifficSign::setPosition(const QVector3D& pos)
{
    m_transform->setTranslation(pos);
}

void TrifficSign::createSymble(const QString& symble)
{
    // add text
    m_symbleTextMesh = new Qt3DExtras::QExtrudedTextMesh();
    m_symbleTextMesh->setDepth(0.0f);
    QFont font("Times New Roman", 32, -1, false);
    m_symbleTextMesh->setFont(font);
    m_symbleTextMesh->setText(symble);

    m_symbleTextMaterial = new Qt3DExtras::QPhongMaterial(this);
    m_symbleTextMaterial->setDiffuse(QColor(200, 250, 00));

    m_symbleTransform = new Qt3DCore::QTransform();
    m_symbleTransform->setTranslation(QVector3D(-1, 1.3f, 0));

    m_symble = new Qt3DCore::QEntity(this);
    m_symble->addComponent(m_symbleTransform);
    m_symble->addComponent(m_symbleTextMesh);
    m_symble->addComponent(m_symbleTextMaterial);
}
