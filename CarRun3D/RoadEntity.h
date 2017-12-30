/**
 *******************************************************************************
 *                       Continental Confidential
 *                  Copyright (c) Continental AG. 2017
 *
 *      This software is furnished under license and may be used or
 *      copied only in accordance with the terms of such license.
 *******************************************************************************
 * @file    RoadEntity.h
 * @brief
 *******************************************************************************
 */
#ifndef ROADENTITY_H
#define ROADENTITY_H

#include "DataDefine.h"

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QPlaneMesh>

class RoadEntity : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    explicit RoadEntity(QNode* parent = nullptr);
    virtual ~RoadEntity();

private:
    Qt3DExtras::QPlaneMesh* m_mesh;
    Qt3DCore::QTransform* m_transform;
    Qt3DExtras::QPhongMaterial* m_material;
};

#endif // ROADENTITY_H
