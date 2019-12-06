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

#include <QSlider>
#include <QSpinBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow) {          // Create a new instance of out UI template

    ui->setupUi(this);                  // Attach the UI template to our MainWindow

    //
    // Here we manually connect the QSpinBox::valueChanged(int) signal to the QSlider::setValue(int) for
    // each of our RGB components so that the slider position is automatically updated when the value of
    // the QSpinBox changes.
    //

    //
    // Method 1 - The old way
    // This is how signals and slots were connected early on on Qts development. It is still used
    // by the MOC when automatically generating connections from Qt Designer but is no longer the
    // recommended method for user code. It relied on the SIGNAL and SLOT macros to generates method
    // signature strings which are then wired together by the MOC (but in C++ macros are evil)
    //

    connect(ui->spinRedValue, SIGNAL(valueChanged(int)), ui->sliderRedValue, SLOT(setValue(int)));

    // Method 2 - The new and improved C++ way
    // As C++ compilers have evolved signal and slot connections have also evolved. With modern C++
    // we can make connections by references the signal/slot methods on each Widget
    //
    // Note: The QSpinBox::valueChanged signal is overloaded as the spin box can contain numeric or
    // text values so there are both QSpinBox::valueChanged(int) and QSpinBox:valueChanged(const QString&)
    // overloads. In this case we need to tell Qt which one we would like to connect. This is done using
    // The QOverload<>::of() helper method.
    //
    // If the signals and slot do not have any overloads we can ommit this (e.g &QSpinBox::valueChanged) and
    // Qt will figure out the method signature.
    //
    // This probably the preferred method for simple connections.
    //

    connect(ui->spinGreenValue, QOverload<int>::of(&QSpinBox::valueChanged), ui->sliderGreenValue, &QSlider::setValue);

    //
    // Method 3 - The C++ guru way ... with Lambdas
    // Perhaps not the best example here since we just need to set a single value, but image you wanted
    // to do more than just set the value of the Blue QSpinBox e.g perhaps change the blue value of another
    // widgets background colour to reflect the change? Well you could do this inside the lambda too.
    //

    connect(ui->spinBlueValue, QOverload<int>::of(&QSpinBox::valueChanged), ui->sliderBlueValue, [=]() {
        ui->sliderBlueValue->setValue(ui->spinBlueValue->value());

        // Add code here for anything else you'd like to do in response to the QSpinBox:valueChanged signal.
    });

}

MainWindow::~MainWindow()
{
    delete ui;                          // Qt usually handles freeing memory for QObject based objects and
                                        // object hierarchies but as the UI template itself does not inherit
                                        // QObject this is one of the cases where we need to free the memory
                                        // ourselves
}

