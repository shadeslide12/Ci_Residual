#include <QDebug>
#include <QString>
#include <QStringList>
#include <QFileDialog>

#include "MainWindow.h"
#include "ui_PreMainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::PreMainWindow)

{
    ui->setupUi(this);

}

MainWindow::~MainWindow(){

    delete ui;
}

