/**
 *******************************************************************************
 *                       Continental Confidential
 *                  Copyright (c) Continental AG. 2017
 *
 *      This software is furnished under license and may be used or
 *      copied only in accordance with the terms of such license.
 *******************************************************************************
 * @file    RoadNodt.h
 * @brief
 *******************************************************************************
 */
#ifndef ROADNODT_H
#define ROADNODT_H

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QPlaneMesh>

class RoadNodt : public Qt3DCore::QEntity
{
public:
    explicit RoadNodt(Qt3DCore::QNode* parent = nullptr);
    virtual ~RoadNodt();

    void moveTo(const QVector3D& pos);

private:
    Qt3DExtras::QPlaneMesh* m_mesh;
    Qt3DCore::QTransform* m_transform;
};

#endif // ROADNODT_H
