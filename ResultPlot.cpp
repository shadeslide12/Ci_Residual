#include "ResultPlot.h"

ResultPlotter::ResultPlotter(QWidget *parent):
        QChart(),series1(new QLineSeries(this)),
        axisX(new QValueAxis(this)),
        axisY(new QValueAxis(this))
{

    setupResultPlot();
}


void ResultPlotter::setupResultPlot() {
    QFont titleFont("Arial",16,QFont::Bold);
    QColor titleColor("Qt::darkBlue");
    setTitle("Performance Curves");
    setTitleFont(titleFont);
    setTitleBrush(titleColor);

    addAxis(axisX,Qt::AlignBottom);
    addAxis(axisY,Qt::AlignLeft);
    addSeries(series1);

    series1->attachAxis(axisX);
    series1->attachAxis(axisY);

    axisX->setTitleText("Iteration");
    axisY->setTitleText("Value");
}