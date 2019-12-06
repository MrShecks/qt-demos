# rgb-picker-demo-4

This is the fourth step in the rgb-picker-demo. It is based rgb-picker-demo-3
with some additional code demonstrating how we can connection signals from one or more ```QObjects``` (QWidgets) to
custom slots on our ```MainWindow``` class.

In the previous step we showed the different ways we can manually make signal/slot connections between UI widgets. But what if we want to do
something a little more complicated. In this example we are going to generate and display the HTML colour code based on the RGB values
selected by the user either via the QSlider or QSpinBox widgets.

And while were at it, why not display the color to the user too?

In Qt Designer I have added two additional widgets:-

- A ```QLineEdit``` to display the HTML colour code (which I have set to read-only)
- A ```QFrame``` to display the actual colour based on the user input

![rgb-picker-demo](../docs/screenshots/rgb-picker-demo-4-001.png)

We'd like the HTML colour code (and colour preview) to update when any of the R, G or B values are changed. To achieve this we need to be able to react to
the ```QSlider::valueChanged(int)``` signal of all 3 sliders, but instead of making connections to 3 different slots, we can connect them all to a single custom
slot that we will add to our ```MainWindow``` class

To define a new slot we first need to add it to the MainWindow class in [MainWindow.h](MainWindow.h) as follows: -

```C++
class MainWindow : public QMainWindow {

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
    Ui::MainWindow *ui;
};
```

Slots are just regular C++ methods so we need to add the body to the CPP implmentation in [MainWindow.cpp](MainWindow.cpp)

```C++
void MainWindow::_onRGBValues_Changed() {

  // TODO: Calculate the HTML colour code based on user input

}
```

Once the custom slot has been defined we can connect it to the ```QSlider::valueChanged()``` signal of all 3 QSlider widgets using one of the manual connection methods shown in the rgb-picker-demo-3

In this example we will use method 2 by placing the following code in the constructor of MainWindow in [MainWindow.cpp](MainWindow.cpp)

```C++
connect(ui->sliderRedValue, &QSlider::valueChanged, this, &MainWindow::_onRGBValues_Changed);
connect(ui->sliderGreenValue, &QSlider::valueChanged, this, &MainWindow::_onRGBValues_Changed);
connect(ui->sliderBlueValue, &QSlider::valueChanged, this, &MainWindow::_onRGBValues_Changed);
```

Once these connections are made our ```MainWindow::_onRGBValues_Changed()``` slot will be called when the user changes any of the sliders

All that remains now is to do something useful in the ```_onRGBValues_Changed()``` slot

```C++
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
```
