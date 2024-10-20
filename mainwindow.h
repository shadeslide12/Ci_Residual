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
    QTimer* timer;
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
    void onRunButtonClicked();

    bool updatePressure(int pressure);
};


#endif //QTTEST_MAINWINDOW_H
