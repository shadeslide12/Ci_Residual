#ifndef QTTEST_RESIDUALPLOT_H
#define QTTEST_RESIDUALPLOT_H

#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
QT_CHARTS_USE_NAMESPACE

class ResidualPlotter : public QChart{
Q_OBJECT

public:
    explicit ResidualPlotter(QWidget* parent = nullptr);

    void updateResidualPlot(const int& iteration,
                            const double& convergence1,
                            const double& convergence2);
private:
    QLineSeries* series_con1;
    QLineSeries* series_con2;
    QValueAxis* axisX;
    QValueAxis* axisY1;
    QValueAxis* axisY2;

    double maxCon1,minCon1;
    double maxCon2,minCon2;
    int maxIteration;    
    //int currentIteration;

    void setupResidualPlot();
};
#endif //QTTEST_RESIDUALPLOT_H
