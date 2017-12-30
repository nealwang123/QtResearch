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

#include "RtvView.h"
#include <QMainWindow>

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

private Q_SLOTS:
    void onCurrentFrameChanged(int index);
    void onPlayFinished();

    void on_addFileBtn_clicked();
    void on_filesListWidget_doubleClicked(const QModelIndex& index);
    void on_playerProgressSlider_sliderMoved(int position);
    void on_playerProgressSlider_sliderPressed();
    void on_playerProgressSlider_sliderReleased();
    void on_playBtn_clicked(bool checked);
    void on_stopBtn_clicked();
    void on_removeFileBtn_clicked();
    void on_removeAllFileBtn_clicked();

    void on_showDetail_clicked(bool checked);

private:
    void initPanel();
    void updatePlayControl();

    bool isFileAdded(const QString& path) const;

private:
    Ui::MainWindow* ui;
    RtvView* mRtvView;
    bool mIsSliderDrag;
};

#endif // MAINWINDOW_H
