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
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QTorusGeometry>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_angle(0)
    , m_sphereMatrix()
{
    ui->setupUi(this);

    initView();

    createTorusEntity();
    createSphereEntity();
    createCuboidEntity();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initView()
{
    m_input = new Qt3DInput::QInputAspect;
    m_rootEntity = new Qt3DCore::QEntity;

    Qt3DExtras::Qt3DWindow* m_view = new Qt3DExtras::Qt3DWindow;
    m_view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x000000)));
    m_view->setRootEntity(m_rootEntity);
    m_view->registerAspect(m_input);

    // camear set
    m_camear = m_view->camera();
    m_camear->lens()->setPerspectiveProjection(45.0f, 16.0 / 9.0, 0.1f, 1000.0f);
    m_camear->setPosition(QVector3D(0, 0, 26));
    m_camear->setViewCenter(QVector3D(0, 0, 0));
    m_camear->setUpVector(QVector3D(0, 1, 0));

    // for camera controls
    //    Qt3DExtras::QFirstPersonCameraController* mCamearController =
    //            new Qt3DExtras::QFirstPersonCameraController(m_rootEntity);
    //    mCamearController->setCamera(m_camear);
    //这个相机更快
    Qt3DExtras::QOrbitCameraController* camController =
            new Qt3DExtras::QOrbitCameraController(m_rootEntity);
    camController->setLinearSpeed(50.0f);
    camController->setLookSpeed(180.0f);
    camController->setCamera(m_camear);

    // light
    m_light = new Qt3DRender::QPointLight;
    m_light->setColor(QColor(QRgb(0xFFFFFF)));
    m_light->setIntensity(1);

    // light transform
    m_lightTransform = new Qt3DCore::QTransform();
    m_lightTransform->setTranslation(m_camear->position());

    // light Entity
    m_lightEntity = new Qt3DCore::QEntity(m_rootEntity);
    m_lightEntity->addComponent(m_light);
    m_lightEntity->addComponent(m_lightTransform);

    QWidget* container = QWidget::createWindowContainer(m_view);
    QSize screenSize = m_view->screen()->size();
    container->setMinimumSize(QSize(200, 100));
    container->setMaximumSize(screenSize);
    ui->viewLayout->addWidget(container);

    // set angle animation
    m_angleAnimation = new QPropertyAnimation;
    m_angleAnimation->setDuration(5000);
    m_angleAnimation->setStartValue(QVariant::fromValue(0));
    m_angleAnimation->setEndValue(QVariant::fromValue(360));
    m_angleAnimation->setTargetObject(this);
    m_angleAnimation->setPropertyName("angle");
    m_angleAnimation->setLoopCount(-1);
    m_angleAnimation->setEasingCurve(QEasingCurve::Linear);

    connect(this, &MainWindow::angleChanged, this, &MainWindow::changeAngle);
    connect(m_camear, SIGNAL(positionChanged(QVector3D)), this,
            SLOT(camearPositionChanged(QVector3D)));

    camearPositionChanged(m_camear->position());
}

void MainWindow::createTorusEntity()
{
    //====================Torus
    // entity============================================
    // set mesh
    m_torus = new Qt3DExtras::QTorusMesh();
    m_torus->setRadius(1.0f);
    m_torus->setMinorRadius(0.3);
    m_torus->setRings(100);
    m_torus->setSlices(20);

    // set transform
    Qt3DCore::QTransform* torusTransform = new Qt3DCore::QTransform();
    torusTransform->setScale(1);
    torusTransform->setRotation(
            QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 25.0f));
    torusTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));

    // set meterial
    Qt3DExtras::QPhongMaterial* torusMaterial = new Qt3DExtras::QPhongMaterial();
    torusMaterial->setDiffuse(QColor(QRgb(0xbeb32b)));
    //    torusMaterial->setAmbient(QColor(QRgb(0xFFFF00)));
    //    torusMaterial->setSpecular(QColor(QRgb(0xCCCCCC)));

    //
    Qt3DCore::QEntity* m_torusEntity = new Qt3DCore::QEntity(m_rootEntity);
    m_torusEntity->addComponent(m_torus);
    m_torusEntity->addComponent(torusMaterial);
    m_torusEntity->addComponent(torusTransform);
}

void MainWindow::createSphereEntity()
{

    Qt3DExtras::QSphereMesh* sphereMesh = new Qt3DExtras::QSphereMesh;
    sphereMesh->setRadius(1);

    m_sphereTransform = new Qt3DCore::QTransform;
    m_sphereTransform->setScale(1.0f);
    m_sphereTransform->setRotation(
            QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), 25));
    m_sphereTransform->setTranslation(QVector3D(5, 0, 0));

    Qt3DExtras::QPhongMaterial* sphereMaterial = new Qt3DExtras::QPhongMaterial();
    sphereMaterial->setDiffuse(QColor(QRgb(0xaeb22a)));

    Qt3DCore::QEntity* m_sphereEntity = new Qt3DCore::QEntity(m_rootEntity);
    m_sphereEntity->addComponent(sphereMesh);
    m_sphereEntity->addComponent(sphereMaterial);
    m_sphereEntity->addComponent(m_sphereTransform);
}

void MainWindow::createCuboidEntity()
{
    Qt3DExtras::QCuboidMesh* cuboidMash = new Qt3DExtras::QCuboidMesh;
    cuboidMash->setShareable(true);
    cuboidMash->setXExtent(4);
    cuboidMash->setYExtent(4);
    cuboidMash->setZExtent(8);

    Qt3DCore::QTransform* cuboidTransform = new Qt3DCore::QTransform;
    cuboidTransform->setScale(1.0f);
    cuboidTransform->setRotation(
            QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), 25));
    cuboidTransform->setTranslation(QVector3D(5, 5, 0));

    Qt3DExtras::QPhongAlphaMaterial* cuboidMaterial =
            new Qt3DExtras::QPhongAlphaMaterial();
    cuboidMaterial->setDiffuse(QColor(QRgb(0xFFFFFF)));
    cuboidMaterial->setAlpha(0.3);
    cuboidMaterial->setShareable(true);
    //    cuboidMaterial->setAmbient(QColor(QRgb(0xFFFF00)));

    Qt3DCore::QEntity* m_cuboidEntity = new Qt3DCore::QEntity(m_rootEntity);
    m_cuboidEntity->addComponent(cuboidMash);
    m_cuboidEntity->addComponent(cuboidMaterial);
    m_cuboidEntity->addComponent(cuboidTransform);

    // small cuboid
    Qt3DExtras::QCuboidMesh* cuboidMash1 = new Qt3DExtras::QCuboidMesh;
    cuboidMash1->setXExtent(2);
    cuboidMash1->setYExtent(2);
    cuboidMash1->setZExtent(6);

    Qt3DCore::QTransform* cuboidTransform1 = new Qt3DCore::QTransform;
    cuboidTransform1->setScale(1.0f);
    cuboidTransform1->setRotation(
            QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), 25));
    cuboidTransform1->setTranslation(QVector3D(5, 5, 0));

    Qt3DExtras::QPhongMaterial* cuboidMaterial1 = new Qt3DExtras::QPhongMaterial();
    cuboidMaterial1->setDiffuse(QColor(QRgb(0x0000ff)));

    Qt3DCore::QEntity* m_cuboidEntity1 = new Qt3DCore::QEntity(m_rootEntity);
    m_cuboidEntity1->addComponent(cuboidMash1);
    m_cuboidEntity1->addComponent(cuboidMaterial1);
    m_cuboidEntity1->addComponent(cuboidTransform1);
}

int MainWindow::getAngle() const
{
    return m_angle;
}

void MainWindow::setAngle(int agl)
{
    m_angle = agl;
    emit angleChanged(agl);
}

void MainWindow::changeAngle(int agl)
{
    qDebug() << "change angle" << agl;
    m_sphereMatrix.setToIdentity();
    m_sphereMatrix.rotate(agl, QVector3D(0.0f, 1.0f, 0.0f));
    m_sphereMatrix.translate(-5.0f, 0.0f, 10.0f);
    m_sphereTransform->setMatrix(m_sphereMatrix);
}

void MainWindow::test(int val)
{
    qDebug() << "val" << val;
}

void MainWindow::camearPositionChanged(const QVector3D& v)
{
    ui->camearX->setValue(v.x());
    ui->camearY->setValue(v.y());
    ui->camearZ->setValue(v.z());
}

void MainWindow::on_scalSlider_valueChanged(int value)
{
    qDebug() << "ring count:" << value;
    m_torus->setRings(value);
}

void MainWindow::on_light_checkBox_toggled(bool checked)
{
    m_lightEntity->setEnabled(checked);
}

void MainWindow::on_light_intensity_valueChanged(int value)
{
    qDebug() << "light intensity:" << value;
    m_light->setIntensity(value);
}

void MainWindow::on_startBtn_clicked()
{
    m_angleAnimation->start();
}

void MainWindow::on_endBtn_clicked()
{
    m_angleAnimation->stop();
}

void MainWindow::on_pauseBtn_clicked()
{
    m_angleAnimation->pause();
}

void MainWindow::on_camearZ_editingFinished()
{
    QVector3D pos = m_camear->position();
    pos.setZ(ui->camearZ->value());
    m_camear->setPosition(pos);
}

void MainWindow::on_camearX_editingFinished()
{
    QVector3D pos = m_camear->position();
    pos.setX(ui->camearX->value());
    m_camear->setPosition(pos);
}

void MainWindow::on_camearY_editingFinished()
{
    QVector3D pos = m_camear->position();
    pos.setY(ui->camearY->value());
    m_camear->setPosition(pos);
}
