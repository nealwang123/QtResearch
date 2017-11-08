/**
 *******************************************************************************
 *                       Continental Confidential
 *                  Copyright (c) Continental AG. 2017
 *
 *      This software is furnished under license and may be used or
 *      copied only in accordance with the terms of such license.
 *******************************************************************************
 * @file    MainWindow.cpp
 * @brief
 *******************************************************************************
 */
#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QScreen>
#include <Qt3DExtras/QForwardRenderer>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mView(new Qt3DExtras::Qt3DWindow)
    , mInput(new Qt3DInput::QInputAspect)
    , mRootEntity(new Qt3DCore::QEntity)
    , mCamear(Q_NULLPTR)
    , mLightEntity(new Qt3DCore::QEntity(mRootEntity))
    , mLight(new Qt3DRender::QPointLight(mLightEntity))
    , mLightTransform(new Qt3DCore::QTransform(mLightEntity))
    , mCoubil(new CoubilNodt(mRootEntity))
    , mCamearController(new Qt3DExtras::QFirstPersonCameraController(mRootEntity))
{
    qRegisterMetaType<RotationDirection>("RotationDirection");
    ui->setupUi(this);
    mView->defaultFrameGraph()->setClearColor(QColor(QRgb(0x000000)));
    QWidget* container = QWidget::createWindowContainer(mView);
    QSize screenSize = mView->screen()->size();
    container->setMinimumSize(QSize(200, 100));
    container->setMaximumSize(screenSize);

    ui->viewLayout->addWidget(container);

    mCamear = mView->camera();
    mCamear->lens()->setPerspectiveProjection(45.0f, 16.0 / 9.0, 0.1f, 1000.0f);
    mCamear->setPosition(QVector3D(0, 0, 20));
    mCamear->setViewCenter(QVector3D(0, 0, 0));
    mCamear->setUpVector(QVector3D(0, 1, 0));

    // light
    mLight->setColor("white");
    mLight->setIntensity(1);
    mLightEntity->addComponent(mLight);

    mLightTransform->setTranslation(mCamear->position());
    mLightEntity->addComponent(mLightTransform);

    // For camera controls
    mCamearController->setCamera(mCamear);

    mView->registerAspect(mInput);
    mView->setRootEntity(mRootEntity);

    // set animation
    mRotateTransformAnimation = new QPropertyAnimation(mLightTransform);
    mRotateTransformAnimation->setTargetObject(mCoubil);
    mRotateTransformAnimation->setDuration(2000);
    mRotateTransformAnimation->setPropertyName("angle");
    mRotateTransformAnimation->setProperty("direct", "Z");
    mRotateTransformAnimation->setStartValue(QVariant::fromValue(0));
    mRotateTransformAnimation->setEndValue(QVariant::fromValue(360));
    mRotateTransformAnimation->setLoopCount(-1);
}

MainWindow::~MainWindow()
{
    delete ui;
    //    delete mInput;
    //    delete mLight;
    //    delete mLightTransform;
    //    delete mLightEntity;
    //    delete mRootEntity;
    //    delete mCamear;
    //    if(mView != Q_NULLPTR)
    //    {
    //        delete mView;
    //        mView = Q_NULLPTR;
    //    }
}

void MainWindow::on_rotationSlider_valueChanged(int value)
{
    QString baseDirect = ui->directComboBox->currentText().trimmed();
    if (baseDirect == "X")
    {
        mCoubil->rotation(RotationDirection::ForX, value);
    }
    else if (baseDirect == "Y")
    {
        mCoubil->rotation(RotationDirection::ForY, value);
    }
    else if (baseDirect == "Z")
    {
        mCoubil->rotation(RotationDirection::ForZ, value);
    }
}

void MainWindow::on_scalSlider_valueChanged(int value)
{
    mCoubil->scalTo(value);
}

void MainWindow::on_directComboBox_currentIndexChanged(const QString& arg1)
{
    mCoubil->setProperty("direct", arg1);
}

void MainWindow::on_startBtn_clicked()
{
    mRotateTransformAnimation->start();
}

void MainWindow::on_endBtn_clicked()
{
    mRotateTransformAnimation->stop();
}
