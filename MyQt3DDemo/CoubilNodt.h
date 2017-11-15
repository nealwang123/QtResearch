/**
 *******************************************************************************
 *                       Continental Confidential
 *                  Copyright (c) Continental AG. 2017
 *
 *      This software is furnished under license and may be used or
 *      copied only in accordance with the terms of such license.
 *******************************************************************************
 * @file    CoubilNodt.h
 * @brief
 *******************************************************************************
 */
#ifndef COUBILNODT_H
#define COUBILNODT_H

#include <QPropertyAnimation>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <QtCore/QObject>

enum class RotationDirection : int
{
    ForX,
    ForY,
    ForZ,

    InVali = -1
};

class CoubilNodt : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString direct READ getDirect WRITE setDirect NOTIFY directChanged)
    //    Q_PROPERTY(float angle READ angle WRITE setAngle NOTIFY angleChanged)
public:
    explicit CoubilNodt(Qt3DCore::QEntity* rootEntity);
    virtual ~CoubilNodt();

    void setAngle(const QVector3D& angle);
    float angle() const;

    void rotation(RotationDirection direction, float ros) const;
    void moveTo(const QVector3D& pos) const;
    void scalTo(int value);
    void scalTo(const QVector3D& scale);

    bool getIsDrag() const;
    void setIsDrag(bool isDrag);

    const QString& getDirect() const;
    void setDirect(const QString& direct);

    void startAnimation();
    void stopAnimation();

Q_SIGNALS:
    void angleChanged();
    void directChanged();

public Q_SLOTS:
    void setEnable(bool enable);

private:
    Qt3DExtras::QCuboidMesh* mCuboid;
    Qt3DCore::QEntity* mRootEntity;
    Qt3DCore::QEntity* mCuboidEntity;
    Qt3DCore::QTransform* mCuboidTransform;
    int mRotationX;
    int mRotationY;
    int mRotationZ;
    bool mIsDrag;
    QString mDirect;
    QPropertyAnimation* mRotateTransformAnimation;
};

#endif // COUBILNODT_H
