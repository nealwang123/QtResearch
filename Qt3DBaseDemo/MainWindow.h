/**
 *******************************************************************************
 *                       Continental Confidential
 *                  Copyright (c) Continental AG. 2017
 *
 *      This software is furnished under license and may be used or
 *      copied only in accordance with the terms of such license.
 *******************************************************************************
 * @file    MainWindow.h
 * @brief
 *******************************************************************************
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QScreen>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QFirstPersonCameraController>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QPhongAlphaMaterial>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DInput/QInputAspect>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QPointLight>

#include <QMatrix4x4>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QTorusMesh>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(int angle READ getAngle WRITE setAngle NOTIFY angleChanged)

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    int getAngle() const;
    void setAngle(int agl);

Q_SIGNALS:
    void angleChanged(int agl);

public Q_SLOTS:
    void changeAngle(int agl);
    void test(int val);
    void camearPositionChanged(const QVector3D& v);

private slots:

    void on_scalSlider_valueChanged(int value);

    void on_light_checkBox_toggled(bool checked);

    void on_light_intensity_valueChanged(int value);

    void on_startBtn_clicked();

    void on_endBtn_clicked();

    void on_pauseBtn_clicked();

    void on_camearZ_editingFinished();

    void on_camearX_editingFinished();

    void on_camearY_editingFinished();

private:
    void initView();
    void createTorusEntity();
    void createSphereEntity();
    void createCuboidEntity();

private:
    Ui::MainWindow* ui;
    Qt3DInput::QInputAspect* m_input; // view input control
    Qt3DCore::QEntity* m_rootEntity;  // view root entity
    Qt3DRender::QCamera* m_camear;
    Qt3DExtras::QOrbitCameraController* camController; // view camera
    //    Qt3DRender::QCamera* m_camear; // view cameara
    Qt3DRender::QPointLight* m_light;       // light render
    Qt3DCore::QTransform* m_lightTransform; // light entity transform
    Qt3DCore::QEntity* m_lightEntity;       // root entity light entity
    QPropertyAnimation* m_angleAnimation;
    int m_angle;

    // sub entity
    Qt3DExtras::QTorusMesh* m_torus;         // torush entity
    Qt3DCore::QTransform* m_sphereTransform; // sphere
    QMatrix4x4 m_sphereMatrix;
};

#endif // MAINWINDOW_H
