#ifndef QTTEST_RESULTPLOT_H
#define QTTEST_RESULTPLOT_H

#include <QChart>
#include <QLineSeries>
#include <QValueAxis>

QT_CHARTS_USE_NAMESPACE

class ResultPlotter : public QChart{
Q_OBJECT

public:
    explicit ResultPlotter(QWidget* parent= nullptr);

private:
    QLineSeries* series1;

    QValueAxis* axisX;
    QValueAxis* axisY;

    void setupResultPlot();
};

#endif //QTTEST_RESULTPLOT_H
