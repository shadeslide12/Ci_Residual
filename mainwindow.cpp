#include "mainwindow.h"
#include "ui_MainWindow.h"
#include "ResidualPlot.h"
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QFileDialog>

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
            ui(new Ui::MainWindow),
            cipherRunner(new CipherRunner(this)),
            setting(new Setting),
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
    connect(ui->Work_Dir_Button,&QPushButton::clicked,this,&MainWindow::onWorkDirButtonClicked);
    connect(ui->Cipher_Dir_Button,&QPushButton::clicked,this,&MainWindow::onCipherDirButtonClicked);
    connect(ui->lineEdit_RunCore,&QLineEdit::returnPressed,this,&MainWindow::onRunCoreButtonClicked);
    connect(ui->AddButton,&QPushButton::clicked,this,&MainWindow::onAddPressureButtonClicked);
    connect(ui->ClearButton,&QPushButton::clicked,this,&MainWindow::onClearPressureButtonClicked);

    connect(cipherRunner, &CipherRunner::s_MessageToLog, this, &MainWindow::onReadStandardOutput);
    connect(cipherRunner, &CipherRunner::s_ErrorToLog, this, &MainWindow::onReadErrors);
    connect(cipherRunner, &CipherRunner::s_UpdateResidual, residualPlotter, &ResidualPlotter::updateResidualPlot);
    connect(cipherRunner, &CipherRunner::s_Cal_Finished, this, &MainWindow::onCal_Finished);
}

MainWindow::~MainWindow(){
    delete setting;
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
    if(currentIndex_Pressure >= pressureList.size()){
        showinLogger("All calculations completed.\n");
        ui->RunButton->setEnabled(true);
        return;
    }

    int currentPressure = pressureList[currentIndex_Pressure];

    if(updatePressure(currentPressure)){
        qDebug()<< "Calculating pressure: "<<currentPressure;
        ui->RunButton->setEnabled(false);
        ui->Log->clear();
        showinLogger("cipher start， Pressure is"+QByteArray::number(currentPressure));
        cipherRunner->runCipher();
    }else{
        showinLogger("Failed to update outlet.dat");
        ui->RunButton->setEnabled(true);
    }
}

void MainWindow::onWorkDirButtonClicked() {
    QString dir = QFileDialog::getExistingDirectory(this,"Select a Work Directory",QDir::homePath());

    if(!dir.isEmpty()){
        setting->setWorkDir(dir);
        ui->lineEdit_WorkDir->setText(dir);
        ui->lineedit_status->setText("Work Dir Updated");
    }
}

void MainWindow::onCipherDirButtonClicked() {
    QString file = QFileDialog::getOpenFileName(this,"select Cipher file",QDir::homePath());
    if(!file.isEmpty()){
        setting->setCipherDir(file);
        ui->lineEdit_CipherPath->setText(file);
        ui->lineedit_status->setText("Cipher Path Updated");
    }
}

void MainWindow::onRunCoreButtonClicked() {
    int runcore = ui->lineEdit_RunCore->text().toInt();
    ui->lineedit_status->setText("Run Core is"+QString::number(runcore));
}

void MainWindow::onAddPressureButtonClicked() {
    double pressure = ui->lineEdit_AddPressure->text().toDouble();
    setting->addPressure(pressure);
    ui->lineedit_status->setText("Add Pressure: "+QString::number(pressure));
}

void MainWindow::onClearPressureButtonClicked() {
    setting->clearPressure();
    ui->lineedit_status->setText("PressureList is cleared now");
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
    qDebug()<<"file open successfully";
    QTextStream in(&outletFile);
    QString content = in.readAll();
    QTextStream out(&outletFile);
    QStringList lines = content.split("\n",Qt::SkipEmptyParts);
    qDebug()<<"content read successfully";

    for(int i=1;i<lines.size();++i){
        QStringList data = lines[i].split(" ",Qt::SkipEmptyParts);

        data[1] = QString::number(pressure);
        lines[i] = data.join("  ");
    }

    outletFile.resize(0);
    out<<lines.join("\n");

    outletFile.close();
    return true;
}

void MainWindow::onCal_Finished(int exitCode, QProcess::ExitStatus exitStatus) {
    if (exitStatus == QProcess::NormalExit && exitCode == 0) {
        showinLogger("Calculation completed successfully for Pressure: "
                        +QByteArray::number(pressureList[currentIndex_Pressure]));
    }else{
        showinLogger("Calculation Failed");
    }

    updateTable();

    currentIndex_Pressure++;
    onRunButtonClicked();
}

void MainWindow::updateTable() {
    ui->Result_Table->setItem(1,2,
                              new QTableWidgetItem(QString::number(666)));
}

void MainWindow::updateResultPlot() {

}