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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//
// Note: To use the multimedia components we need to link the
// multimedia libraries, see audio-player.pro
//

#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

    static constexpr quint32 MILLIS_PER_SECOND = 1000;
    static constexpr quint32 MILLIS_PER_MINUTE = MILLIS_PER_SECOND * 60;
    static constexpr quint32 MILLIS_PER_HOUR = MILLIS_PER_MINUTE * 60;

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void _onMenu_openFileClicked();

    void _onMedia_durationChanged(quint64 duration);
    void _onMedia_positionChanged(quint64 position);

private:
    Ui::MainWindow* _ui;
    QMediaPlayer _mediaPlayer;

    void openMediaFile(const QString& fileName);
    QString formatMediaTime(quint64 timeInMillis);
};
#endif // MAINWINDOW_H
