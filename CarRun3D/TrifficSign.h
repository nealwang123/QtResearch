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
#include <Qt3DExtras/QPhongMaterial>

class TrifficSign : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    explicit TrifficSign(QNode* parent = nullptr);
    virtual ~TrifficSign();

    void setPosition(const QVector3D& pos);

private:
    Qt3DExtras::QCuboidMesh* m_mesh;
    Qt3DCore::QTransform* m_transform;
    Qt3DExtras::QPhongMaterial* m_material;
};

#endif // TRIFFICSIGN_H
