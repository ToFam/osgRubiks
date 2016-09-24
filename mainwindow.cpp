#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->turnBlue, &QPushButton::pressed, this,      [this](){ ui->widget->rotate(RubiksCube::BLUE,     true); });
    connect(ui->turnBlueInv, &QPushButton::pressed, this,   [this](){ ui->widget->rotate(RubiksCube::BLUE,     false); });
    connect(ui->turnGreen, &QPushButton::pressed, this,     [this](){ ui->widget->rotate(RubiksCube::GREEN,    true); });
    connect(ui->turnGreenInv, &QPushButton::pressed, this,  [this](){ ui->widget->rotate(RubiksCube::GREEN,    false); });
    connect(ui->turnYellow, &QPushButton::pressed, this,    [this](){ ui->widget->rotate(RubiksCube::YELLOW,   true); });
    connect(ui->turnYellowInv, &QPushButton::pressed, this, [this](){ ui->widget->rotate(RubiksCube::YELLOW,   false); });
    connect(ui->turnRed, &QPushButton::pressed, this,       [this](){ ui->widget->rotate(RubiksCube::RED,      true); });
    connect(ui->turnRedInv, &QPushButton::pressed, this,    [this](){ ui->widget->rotate(RubiksCube::RED,      false); });
    connect(ui->turnOrange, &QPushButton::pressed, this,    [this](){ ui->widget->rotate(RubiksCube::ORANGE,   true); });
    connect(ui->turnOrangeInv, &QPushButton::pressed, this, [this](){ ui->widget->rotate(RubiksCube::ORANGE,   false); });
    connect(ui->turnWhite, &QPushButton::pressed, this,     [this](){ ui->widget->rotate(RubiksCube::WHITE,    true); });
    connect(ui->turnWhiteInv, &QPushButton::pressed, this,  [this](){ ui->widget->rotate(RubiksCube::WHITE,    false); });

    connect(ui->reset, SIGNAL(pressed()), ui->widget, SLOT(reset()));
    connect(ui->scramble, SIGNAL(pressed()), ui->widget, SLOT(scramble()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
