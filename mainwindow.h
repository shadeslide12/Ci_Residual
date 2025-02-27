#ifndef QTTEST_MAINWINDOW_H
#define QTTEST_MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QButtonGroup>
#include <QChartView>
#include <QChart>
#include <QTimer>
#include <QThread>
#include "ResidualPlot.h"
#include "ResultPlot.h"
#include "CipherRunner.h"
#include "setting.h"

QT_CHARTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
Q_OBJECT

public:
    explicit MainWindow(QWidget* parent=nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow* ui;

    CipherRunner* cipherRunner;
    Setting* setting;
    QButtonGroup* slidergroup;

    QChartView* residualPlotterView;
    QChartView* resultPlotterView;
    ResidualPlotter* residualPlotter;
    ResultPlotter* resultPlotter;

    QVector<int> pressureList;
    int currentIndex_Pressure;

    void initialUi();
    void showinLogger(const QByteArray& log);
    void onReadStandardOutput(const QByteArray& Message);
    void onReadErrors(const QByteArray& Errors);
    void updateTable();
    void updateResultPlot();

    void onRunButtonClicked();
    void onWorkDirButtonClicked();
    void onCipherDirButtonClicked();
    void onRunCoreButtonClicked();
    void onAddPressureButtonClicked();
    void onClearPressureButtonClicked();

    void onCal_Finished(int exitCode, QProcess::ExitStatus exitStatus);
    bool updatePressure(int pressure);
};


#endif //QTTEST_MAINWINDOW_H
