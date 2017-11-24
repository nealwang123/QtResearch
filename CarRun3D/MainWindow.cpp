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

#include <QDebug>
#include <QScreen>
#include <Qt3DExtras/QForwardRenderer>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_input(Q_NULLPTR)
    , m_view(Q_NULLPTR)
    , m_camear(Q_NULLPTR)
    , m_camearController(Q_NULLPTR)
    , m_rootEntity(Q_NULLPTR)
    , m_light(Q_NULLPTR)
    , m_lightTransform(Q_NULLPTR)
    , m_lightEntity(Q_NULLPTR)
    , m_car(Q_NULLPTR)
{
    ui->setupUi(this);
    m_input = new Qt3DInput::QInputAspect;
    m_rootEntity = new Qt3DCore::QEntity;

    m_view = new Qt3DExtras::Qt3DWindow;
    m_view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x000000)));
    m_view->setRootEntity(m_rootEntity);
    m_view->registerAspect(m_input);

    //![1]
    // camear
    m_camear = m_view->camera();
    m_camear->lens()->setPerspectiveProjection(45.0f, 16.0 / 9.0f, 0.01, 1000.0f);
    m_camear->setPosition(QVector3D(0, 45, 10));
    m_camear->setViewCenter(QVector3D(0, 0, 0));
    m_camear->setUpVector(QVector3D(0, 1, 0));

    // camear controller
    m_camearController = new Qt3DExtras::QOrbitCameraController(m_rootEntity);
    m_camearController->setLinearSpeed(50.0f);
    m_camearController->setLookSpeed(180.0f);
    m_camearController->setCamera(m_camear);

    //![1]

    //![2]
    // light
    m_light = new Qt3DRender::QPointLight;
    m_light->setColor(QColor(QRgb(0xffffff)));

    // light transform
    m_lightTransform = new Qt3DCore::QTransform();
    m_lightTransform->setTranslation(m_camear->position());

    // light Entity
    m_lightEntity = new Qt3DCore::QEntity(m_rootEntity);
    m_lightEntity->addComponent(m_light);
    m_lightEntity->addComponent(m_lightTransform);
    //![2]

    QWidget* container = QWidget::createWindowContainer(m_view);
    container->setMinimumSize(QSize(200, 100));
    container->setMaximumSize(m_view->screen()->size());
    setCentralWidget(container);

    // add road entity
    m_road = new RoadEntity(m_rootEntity);

    // add car entity
    m_car = new CarEntity(m_rootEntity);

    // add triffice
    setTriffic();

    connect(m_car, &CarEntity::posionChanged, this, &MainWindow::carPostionChanged);
    connect(m_camear, &Qt3DRender::QCamera::positionChanged, this,
            &MainWindow::on_camear_position_changed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTriffic()
{
    int triCount = glob_roadLength / 20;
    for (int i = 0; i < triCount; ++i)
    {
        TrifficSign* tri = new TrifficSign(m_rootEntity);
        tri->setPosition(QVector3D(-glob_roadWidth / 2 + 0.25, 2, -i * 20));
    }
}

void MainWindow::carPostionChanged()
{
    Qt3DCore::QTransform* carTransform = m_car->getTransform();
    if (carTransform == Q_NULLPTR)
    {
        return;
    }
    QVector3D camearPosition = m_camear->position();
    camearPosition.setZ(10 + carTransform->translation().z());
    m_camear->setPosition(camearPosition);
    m_camear->setViewCenter(QVector3D(0, 0, carTransform->translation().z()));
    m_camear->setUpVector(QVector3D(0, 1, 0));
    qDebug() << carTransform->translation().z();
}

void MainWindow::on_runBtn_clicked(bool checked)
{
    ui->runBtn->setText(checked ? "pause" : "run");
    m_car->startRun(checked);
}

void MainWindow::on_stopBtn_clicked()
{
    m_car->stopRun();
}

void MainWindow::on_light_checkBox_toggled(bool checked)
{
    m_lightEntity->setEnabled(checked);
}

void MainWindow::on_light_intensity_valueChanged(int value)
{
    m_light->setIntensity(value);
}

void MainWindow::on_camear_position_changed(const QVector3D& pos)
{
    ui->camearPostionX->setText(QString::number(pos.x()));
    ui->camearPostionY->setText(QString::number(pos.y()));
    ui->camearPostionZ->setText(QString::number(pos.z()));
}
