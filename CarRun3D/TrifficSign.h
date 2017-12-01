/**
 *******************************************************************************
 *                       Continental Confidential
 *                  Copyright (c) Continental AG. 2017
 *
 *      This software is furnished under license and may be used or
 *      copied only in accordance with the terms of such license.
 *******************************************************************************
 * @file    TrifficSign.h
 * @brief
 *******************************************************************************
 */
#ifndef TRIFFICSIGN_H
#define TRIFFICSIGN_H

#include "DataDefine.h"
#include <QMatrix4x4>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QExtrudedTextMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QTextureMaterial>

#include <Qt3DExtras/QExtrudedTextMesh>
#include <Qt3DRender/QTextureImage>

class TrifficSign : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    explicit TrifficSign(const QString& symble, QNode* parent = nullptr);
    virtual ~TrifficSign();

    void setPosition(const QVector3D& pos);

private:
    void createSymble(const QString& symble);

private:
    Qt3DExtras::QCuboidMesh* m_mesh;
    Qt3DCore::QTransform* m_transform;
    Qt3DExtras::QPhongMaterial* m_material;
    Qt3DExtras::QTextureMaterial* m_textureMaterial;

    Qt3DCore::QEntity* m_symble;
    Qt3DCore::QTransform* m_symbleTransform;
    Qt3DExtras::QExtrudedTextMesh* m_symbleTextMesh;
    Qt3DExtras::QPhongMaterial* m_symbleTextMaterial;
};

#endif // TRIFFICSIGN_H
