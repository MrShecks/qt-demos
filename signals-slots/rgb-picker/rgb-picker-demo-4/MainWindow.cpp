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
    // If the signals and slot do not have any overloads we can ommit this (e.g &QSpingBox::valueChanged) and
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

    //
    // To make the demo application somewhat useful lets calculate the HTML colour code for the selected
    // RGB values and display it in the textHtmlColor QLineEdit. We'd like the HTML colour to be re-built
    // when any of the individual R, G or B components change so we can connect the "valueChanged(int)"
    // signal of all 3 QSlider widgets to a custom slot "_onRGBValues_Changed" on our MainWindow class.
    //
    // Note: We'll use method 3 for the connections to demonstrate calling a custom slot.
    //
    // Also note: Even though QSlider::valueChanged(int) has an int paramters, we don't need it
    // so out custom slot takes no parameters, Qt will just ignore the parameter in this case.
    //
    // Also also of note: We have only connected our custom slot to the QSlider::valueChanged() signal
    // but it will still be called indirectly when the values of the QSpinBox widges are changed as
    // these have already been connected to the QSlider::setValue() slots, so we have a chain effect.
    //

    connect(ui->sliderRedValue, &QSlider::valueChanged, this, &MainWindow::_onRGBValues_Changed);
    connect(ui->sliderGreenValue, &QSlider::valueChanged, this, &MainWindow::_onRGBValues_Changed);
    connect(ui->sliderBlueValue, &QSlider::valueChanged, this, &MainWindow::_onRGBValues_Changed);

    // Just a little OCD fix, we should show the HTML code based on the default values of the sliders
    // when the application starts ... we can do this by just calling our slot directly here.

    _onRGBValues_Changed();
}

MainWindow::~MainWindow()
{
    delete ui;                          // Qt usually handles freeing memory for QObject based objects and
                                        // object hierarchies but as the UI template itself does not inherit
                                        // QObject this is one of the cases where we need to free the memory
                                        // ourselves
}

void MainWindow::_onRGBValues_Changed() {

    // The slot will be called when any of the QSlider::valueChanged() signals are fired but
    // we need all 3 RGB component values to build our HTML colour code, so we just query the
    // properties of each slider.

    int red = ui->sliderRedValue->value();
    int green = ui->sliderGreenValue->value();
    int blue = ui->sliderBlueValue->value();

    // A little bit of QString formatting magic ... (see https://doc.qt.io/qt-5/qstring.html#arg)

    QString htmlColor = QString("#%1%2%3")
            .arg(red, 2, 16, QChar('0'))
            .arg(green, 2, 16, QChar('0'))
            .arg(blue, 2, 16, QChar('0'));

    // And we can update the text of the QLineEdit to display our new HTML color code.

    ui->textHtmlColor->setText(htmlColor);

    // As a bonus, since we already have the RGB color, lets display it in the QFrame widget

    QPalette palette = ui->frameColorPreview->palette();

    palette.setColor (QPalette::Background, QColor::fromRgb(red, green, blue));

    ui->frameColorPreview->setAutoFillBackground(true);
    ui->frameColorPreview->setPalette(palette);
}

