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

#include "MainWindow.h"

// The Qt MOC has generated code to help build our UI (based on MainWindow.ui)
// for us so we need to pull in the template here

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow) {          // Create a new instance of out UI template

    ui->setupUi(this);                  // Attach the UI template to our MainWindow
}

MainWindow::~MainWindow()
{
    delete ui;                          // Qt usually handles freeing memory for QObject based objects and
                                        // object hierarchies but as the UI template itself does not inherit
                                        // QObject this is one of the cases where we need to free the memory
                                        // ourselves
}

