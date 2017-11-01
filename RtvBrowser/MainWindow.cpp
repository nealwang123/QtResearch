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
#include <QFileDialog>
#include <QFileInfo>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mRtvView(new RtvView(this))
    , mIsSliderDrag(false)
{
    ui->setupUi(this);
    ui->ViewSceneLayout->addWidget(mRtvView);
    connect(mRtvView, &RtvView::currentFrameChanged, this,
            &MainWindow::onCurrentFrameChanged);
    connect(mRtvView, &RtvView::playFinished, this, &MainWindow::onPlayFinished);
    ui->playListDockWidget->setVisible(true);
    updatePlayControl();

    setMinimumSize(960, 640);
    adjustSize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCurrentFrameChanged(int index)
{
    if (!mIsSliderDrag)
    {
        ui->playerProgressSlider->setValue(index);
    }
}

void MainWindow::onPlayFinished()
{
    on_stopBtn_clicked();
}

void MainWindow::on_addFileBtn_clicked()
{
    QStringList fileList =
            QFileDialog::getOpenFileNames(this, tr("Add Rtv into play list"),
                                          qApp->applicationDirPath(),
                                          "RTV(*.rtv)");

    for (QString filePath : fileList)
    {
        if (isFileAdded(filePath))
        {
            continue;
        }

        QFileInfo fileInf(filePath);
        QListWidgetItem* item = new QListWidgetItem(fileInf.fileName());
        item->setData(Qt::UserRole, fileInf.filePath());
        item->setToolTip(fileInf.filePath());
        ui->filesListWidget->addItem(item);
    }
}

void MainWindow::on_filesListWidget_doubleClicked(const QModelIndex& index)
{
    QFileInfo fileInfo(index.data(Qt::UserRole).toString());

    if (!fileInfo.exists())
    {
        qDebug() << "file not is exists!" << fileInfo.filePath();
        return;
    }

    on_stopBtn_clicked();

    bool ok = mRtvView->initalize(fileInfo.filePath());
    if (ok)
    {
        initPanel();
        ui->rtvTitleLabel->setText("Current RTV: " + fileInfo.baseName());
        mRtvView->goTo(0);
    }
    qDebug() << "Initialize rtv file succeed?" << ok;
}

void MainWindow::initPanel()
{
    const Head& rtvInfo = mRtvView->getRtvInfo();
    ui->playerProgressSlider->setMaximum(rtvInfo.frames_count);
    ui->playerProgressSlider->setValue(0);
    ui->playControlPanel->setEnabled(true);
    ui->playBtn->setEnabled(true);
    ui->stopBtn->setEnabled(false);
}

void MainWindow::updatePlayControl()
{
    bool videoReady = mRtvView->isReady();
    bool stopped = mRtvView->isStopped();
    ui->playControlPanel->setEnabled(videoReady);
    ui->playBtn->setEnabled(videoReady);
    ui->stopBtn->setEnabled(videoReady && !stopped);
    ui->playerProgressSlider->setEnabled(!stopped);
}

bool MainWindow::isFileAdded(const QString& path) const
{
    for (int i = 0; i < ui->filesListWidget->count(); ++i)
    {
        QListWidgetItem* item = ui->filesListWidget->item(i);
        if (item != Q_NULLPTR && item->data(Qt::UserRole).toString() == path)
        {
            return true;
        }
    }

    return false;
}

void MainWindow::on_playerProgressSlider_sliderPressed()
{
    mIsSliderDrag = true;
}

void MainWindow::on_playerProgressSlider_sliderReleased()
{
    mIsSliderDrag = false;
}

void MainWindow::on_playerProgressSlider_sliderMoved(int position)
{
    if (position == ui->playerProgressSlider->value())
    {
        return;
    }

    mRtvView->goTo(position);
}

void MainWindow::on_playBtn_clicked(bool checked)
{
    if (checked)
    {
        mRtvView->play();
    }
    else
    {
        mRtvView->pause();
    }

    updatePlayControl();
}

void MainWindow::on_stopBtn_clicked()
{
    mRtvView->stop();
    ui->playBtn->setChecked(false);
    onCurrentFrameChanged(0);
    updatePlayControl();
}

void MainWindow::on_removeFileBtn_clicked()
{
    QListWidgetItem* item =
            ui->filesListWidget->takeItem(ui->filesListWidget->currentRow());
    if (item != Q_NULLPTR)
    {
        delete item;
        item = Q_NULLPTR;
    }
}

void MainWindow::on_removeAllFileBtn_clicked()
{
    ui->filesListWidget->clear();
}

void MainWindow::on_showDetail_clicked(bool checked)
{
    mRtvView->setEnableShowDetail(checked);
}
