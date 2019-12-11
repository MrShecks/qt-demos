/*
 * File: %{Cpp:License:FileName}
 * Created: 2019-12-11
 *
 * Copyright (c) shecks 2019 <shecks@gmail.com>
 * All rights reserved.
 *
 * This file is part of %QT_PROJECT_NAME%.
 *
 * %QT_PROJECT_NAME% is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * %QT_PROJECT_NAME% is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with %QT_PROJECT_NAME%.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      _ui(new Ui::MainWindow) {

    _ui->setupUi(this);

    // Connect our QPushButton clicked signals to the appropriate slots on the QMediaPlayer
    // component so we can control playback

    connect(_ui->buttonPlay, &QPushButton::clicked, &_mediaPlayer, &QMediaPlayer::play);
    connect(_ui->buttonStop, &QPushButton::clicked, &_mediaPlayer, &QMediaPlayer::stop);
    connect(_ui->buttonPause, &QPushButton::clicked, &_mediaPlayer, &QMediaPlayer::pause);

    // We need to know the length of the selected media file so that we can set the maximum value
    // for the position QSlider. The for some media sources the QMediaPlayer component may not
    // know the duration immediately but will emit the "durationChanged" signal when it is changed
    // so we connect to that signal an update he UI when it's fired.

    connect(&_mediaPlayer, &QMediaPlayer::durationChanged, this, &MainWindow::_onMedia_durationChanged);

    // We want the track position QSlider to automatically update its value as the media positions changes
    // so we connect to the QMediaPlayer::positionChanged signal. This signal gives the the play position
    // in milliseconds so we can also update the playback time label too.

    connect(&_mediaPlayer, &QMediaPlayer::positionChanged, this, &MainWindow::_onMedia_positionChanged);

    // We want the QMediaPlayer playback position to change when the user moves the playback
    // position QSlider, since we set the QSlider range to 0 -> <Media Duration> we can just
    // connect the QSlider::valueChanged() signal directly to the QMediaPlayer::setPosition()
    // slot in order to achieve this.

    connect(_ui->sliderCurrentPosition, &QSlider::valueChanged, &_mediaPlayer, &QMediaPlayer::setPosition);

    // Connect up our menu seleciton signals

    connect(_ui->actionOpen, &QAction::triggered, this, &MainWindow::_onMenu_openFileClicked);

    // Note: Because this is just a demo we don't need todo anything special when the exit
    // menu option is clicked (e.g prompting to save or asking for confirmation) so we can
    // connect the "triggered" signal directly to the QMainWindow:close slot

    connect(_ui->actionExit, &QAction::triggered, this, &MainWindow::close);

    // For testing we can just call openMediaFile() to pre-load a file so we don't
    // need to select one each time we run the application

    //openMediaFile("/home/shecks/Documents/Heroes (Motorhead Bowie Cover).mp3");
}

MainWindow::~MainWindow() {
    delete _ui;
}

void MainWindow::_onMenu_openFileClicked() {

    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open Media"),
                QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).last(),
                tr("Media Files (*.mp3)")
    );

    if(!fileName.isEmpty()) {
        openMediaFile(fileName);
    }
}

void MainWindow::_onMedia_durationChanged(quint64 duration) {

    //
    // Setting the min/max values for the track postion QSlider
    // based on the duration of the selected media
    //

    _ui->sliderCurrentPosition->setMinimum(0);
    _ui->sliderCurrentPosition->setMaximum(duration);
}

void MainWindow::_onMedia_positionChanged(quint64 position) {

    //
    // Here we are updating the track position time and the position
    // of the track position QSlider handle based on the current time
    // position of the selected media
    //

    _ui->labelCurrentTime->setText(formatMediaTime(position));
    _ui->sliderCurrentPosition->setValue(position);
}

void MainWindow::openMediaFile(const QString& fileName) {
    _mediaPlayer.setMedia(QUrl::fromLocalFile(fileName));

    _ui->buttonPlay->setEnabled(true);
    _ui->buttonPause->setEnabled(true);
    _ui->buttonStop->setEnabled(true);
    _ui->sliderCurrentPosition->setEnabled(true);
}

QString MainWindow::formatMediaTime(quint64 timeInMillis) {
    quint64 hours, minutes, seconds;

    hours = timeInMillis / MILLIS_PER_HOUR;
    timeInMillis -= (hours * MILLIS_PER_HOUR);
    minutes = timeInMillis / MILLIS_PER_MINUTE;
    timeInMillis -= minutes * MILLIS_PER_MINUTE;
    seconds = timeInMillis / MILLIS_PER_SECOND;

    timeInMillis -= seconds * MILLIS_PER_SECOND;

    return QString("%1:%2:%3")
            .arg(hours, 2, 10, QChar('0'))
            .arg(minutes, 2, 10, QChar('0'))
            .arg(seconds, 2, 10, QChar('0'));
}
