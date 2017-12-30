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
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QFirstPersonCameraController>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DInput/QInputAspect>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QPointLight>

#include "MyCarEntity.h"
#include "RoadNodt.h"

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

private slots:
    void on_rotationSlider_valueChanged(int value);
    void on_scalSlider_valueChanged(int value);
    void on_directComboBox_currentIndexChanged(const QString& arg1);
    void on_startBtn_clicked();

    void on_endBtn_clicked();

private:
    Ui::MainWindow* ui;
    Qt3DExtras::Qt3DWindow* mView;
    Qt3DInput::QInputAspect* mInput;
    Qt3DCore::QEntity* mRootEntity;
    Qt3DRender::QCamera* mCamear;
    Qt3DExtras::QFirstPersonCameraController* mCamearController;
    Qt3DCore::QEntity* mLightEntity;
    Qt3DRender::QPointLight* mLight;
    Qt3DCore::QTransform* mLightTransform;
    RoadNodt* mRoadNodt;
    MyCarEntity* mCar;
};

#endif // MAINWINDOW_H
