#ifndef QTTEST_MAINWINDOW_H
#define QTTEST_MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QButtonGroup>
#include <QChartView>
#include <QChart>
#include <QTimer>
#include "ResidualPlot.h"
#include "ResultPlot.h"

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

    QProcess* process;
    QTimer* timer;
    QButtonGroup* slidergroup;

    QChartView* residualPlotterView;
    QChartView* resultPlotterView;
    ResidualPlotter* residualPlotter;
    ResultPlotter* resultPlotter;

    void initialUi();
    void showinLogger(const QByteArray& log);
    void onReadStandardOutput();
    void onReadErrors();
    void onRunButtonClicked();
};


#endif //QTTEST_MAINWINDOW_H
