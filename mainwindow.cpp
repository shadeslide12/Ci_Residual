#include "mainwindow.h"
#include "ui_MainWindow.h"
#include "ResidualPlot.h"
#include <QDebug>
#include <QString>
#include <QStringList>

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
            ui(new Ui::MainWindow),
            cipherRunner(new CipherRunner(this)),
            timer(new QTimer(this)),
            residualPlotter(new ResidualPlotter),
            resultPlotter(new ResultPlotter),
            slidergroup(new QButtonGroup(this))
            {
    ui->setupUi(this);

    pressureList = {100000,110000,120000};
    currentIndex_Pressure = 0;

    residualPlotterView = new QChartView(this);
    resultPlotterView = new QChartView(this);
    initialUi();
    connect(ui->RunButton,&QPushButton::clicked,this,&MainWindow::onRunButtonClicked);
    connect(cipherRunner,&CipherRunner::messageToLog,this,&MainWindow::onReadStandardOutput);
    connect(cipherRunner,&CipherRunner::errorToLog,this,&MainWindow::onReadErrors);
    //connect(timer,&QTimer::timeout,residualPlotter,&ResidualPlotter::updateResidualPlot);
    connect(cipherRunner, &CipherRunner::s_UpdateResidual, residualPlotter, &ResidualPlotter::updateResidualPlot);
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
    cipherRunner->runCipher();
}

void MainWindow::showinLogger(const QByteArray& log) {
    QString logRead = QString::fromUtf8(log);
    ui->Log->appendPlainText(logRead);
}

void MainWindow::onReadStandardOutput(const QByteArray &Message) {
    showinLogger(Message);
}

void MainWindow::onReadErrors(const QByteArray &Errors)  {
    QString errorOutput = QString::fromUtf8(Errors);
    QStringList lines = errorOutput.split("\n");

    for(const QString& line: lines){
        qDebug()<<line;
    }
}

bool MainWindow::updatePressure(int pressure) {
    QFile outletFile("./BC_files/r67-outflow-outlet.dat");
    if(!outletFile.open(QIODevice::ReadWrite | QIODevice::Text)){
        return false;
    }

    QTextStream in(&outletFile);
    QString content = in.readAll();
    outletFile.resize(0);

    QTextStream out(&outletFile);
    QStringList lines = content.split("\n");

    for(int i=0;i<lines.size();++i){
        QStringList data = lines[i].split(" ",Qt::SkipEmptyParts);

        data[1] = QString::number(pressure);
        lines[i] = data.join("  ");
    }

    outletFile.resize(0);
    out<<lines.join("\n");

    outletFile.close();
    return true;


}