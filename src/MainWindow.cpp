#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSizePolicy policy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    policy.setHeightForWidth(true);
    painter.setSizePolicy(policy);
    ui->glWidgetLayout->addWidget(&painter);
    connect(ui->startPushButton, &QPushButton::pressed, this, &MainWindow::startSim);
}

MainWindow::~MainWindow()
{
    delete ui;
}

