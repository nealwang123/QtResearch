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

#include "CarEntity.h"
#include "RoadEntity.h"
#include "TrifficSign.h"

#include <QMainWindow>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DInput/QInputAspect>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QPointLight>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    void setTriffic();

public Q_SLOTS:
    void carPostionChanged();

private slots:

    void on_runBtn_clicked(bool checked);

    void on_stopBtn_clicked();

    void on_light_checkBox_toggled(bool checked);

    void on_light_intensity_valueChanged(int value);

    void on_camear_position_changed(const QVector3D& pos);

private:
    Ui::MainWindow* ui;

    Qt3DInput::QInputAspect* m_input;
    Qt3DExtras::Qt3DWindow* m_view;
    Qt3DRender::QCamera* m_camear;
    Qt3DExtras::QOrbitCameraController* m_camearController;
    Qt3DCore::QEntity* m_rootEntity;
    Qt3DRender::QPointLight* m_light;
    Qt3DCore::QTransform* m_lightTransform;
    Qt3DCore::QEntity* m_lightEntity;

    RoadEntity* m_road;
    CarEntity* m_car;
};

#endif // MAINWINDOW_H
