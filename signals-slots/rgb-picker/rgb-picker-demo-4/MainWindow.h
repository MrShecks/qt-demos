/*
 * File: %{Cpp:License:FileName}
 * Created: 2019-12-6
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
// When using the Qt Designer to build our user interface it will generate
// a .ui file with the same name as our class. During compilation Qts
// Meta Object Compiler (MOC) will compile the .ui file to produce a .CCP
// source and .H header file containing the the code to build our UI.
//
// In this case the files will be named ui_MainWindow.h and moc_MainWindow.cpp
// These are intermediate file so will be re-generated when the .ui file is
// modified. You should never really need to look at these files unless something
// strange is going on and you need to debug problems with the UI (very rare)
//
// The ui_MainWindow.h file contains a template for our UI and because it will
// be named MainWindow it is common practice to place it in the "Ui" namespace
// so that it doesn't clash with our "MainWindow" class definition below.
//
// So MainWindow is our class and Ui:MainWindow is the UI template class.
//
// Note: Qt has generated this code for us.

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {

    //
    // Note: All objects that make use of the Qts signals/slots mechanism must both
    // inherit from QObject or one of its subclasses (QWMainWindow in this case) AND
    // include the Q_OBJECT macro in its class definition.
    //
    // As a side note it is important that the Q_OBJECT macro is defined in a header
    // file as Qt Meta Object Compiler (MOC) doesn't support parsing Q_OBJECT definitions
    // in CPP files (This will be relavant if you ever want to have a private class
    // in a CPP source module that needs to use signals and slots)
    //

    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:

    //
    // Here we delare a custom slot on our MainWindow class. This slot will be connected to the
    // "valueChanged()" signal of each of out RGB QSliders so that when any value changes we
    // can do some processing.
    //

    void _onRGBValues_Changed();

private:

    //
    // This is a pointer to an instance of the UI template class generated
    // by the Qt MOC. Note we need to reference it via the "Ui" namespace
    // that Qt setup for us at the top of the file
    //

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
