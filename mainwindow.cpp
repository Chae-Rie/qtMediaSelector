#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCreatingMedia_triggered()
{
    QFormLayout* qFormlayout = new QFormLayout;



    int i = 1;
    delete qFormlayout;
}



