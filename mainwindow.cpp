#include "mainwindow.h"
#include "ui_MainWindow.h"
#include "ResidualPlot.h"
#include <QDebug>
#include <QString>
#include <QStringList>

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
            ui(new Ui::MainWindow),
            timer(new QTimer(this)),
            residualPlotter(new ResidualPlotter),
            resultPlotter(new ResultPlotter),
            slidergroup(new QButtonGroup(this))
            {
    ui->setupUi(this);
    process = new QProcess(this);
    residualPlotterView = new QChartView(this);
    resultPlotterView = new QChartView(this);
    initialUi();
    connect(ui->RunButton,&QPushButton::clicked,this,&MainWindow::onRunButtonClicked);
    connect(process,&QProcess::readyReadStandardOutput,this,&MainWindow::onReadStandardOutput);
    connect(process,&QProcess::readyReadStandardError,this,&MainWindow::onReadErrors);
    connect(timer,&QTimer::timeout,residualPlotter,&ResidualPlotter::updateResidualPlot);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::initialUi(){
    ui->Layout_ResidualPlot->addWidget(residualPlotterView);
    residualPlotterView->setChart(residualPlotter);
    ui->Layout_CanvasResult->addWidget(resultPlotterView);
    resultPlotterView->setChart(resultPlotter);

    slidergroup->addButton(ui->TabRunButton);
    slidergroup->addButton(ui->TabResultButton);
    slidergroup->addButton(ui->TabStaticsButton);
    slidergroup->addButton(ui->TabSettingButton);
    slidergroup->setExclusive(true);

    connect(ui->TabRunButton,&QPushButton::clicked,[this](){ui->MainBody->setCurrentIndex(0);});
    connect(ui->TabResultButton,&QPushButton::clicked,[this](){ui->MainBody->setCurrentIndex(1);});
    connect(ui->TabStaticsButton,&QPushButton::clicked,[this](){ui->MainBody->setCurrentIndex(2);});
    connect(ui->TabSettingButton,&QPushButton::clicked,[this](){ui->MainBody->setCurrentIndex(3);});


}

void MainWindow::onRunButtonClicked() {
    qDebug()<<"cipher started";
    ui->RunButton->setEnabled(false);
    ui->Log->clear();
    timer->setInterval(1000);
    timer->start();
    showinLogger("cipher start");
    process->start("mpirun",QStringList()<<"-np"<<"10"<<"./cipher-1.0.5");
}

void MainWindow::showinLogger(const QByteArray& log) {
    QString logRead = QString::fromUtf8(log);
    ui->Log->appendPlainText(logRead);
}

void MainWindow::onReadStandardOutput() {
    showinLogger(process->readAllStandardOutput());
}

void MainWindow::onReadErrors() {
    QString errorOutput = QString::fromUtf8(process->readAllStandardError());
    QStringList lines = errorOutput.split("\n");

    for(const QString& line: lines){
        qDebug()<<line;
    }
}