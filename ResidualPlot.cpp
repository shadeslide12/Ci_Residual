#include "ResidualPlot.h"

ResidualPlotter::ResidualPlotter(QWidget* parent):
        QChart(),series_con1(new QLineSeries(this)),
        series_con2(new QLineSeries(this)),
        axisX(new QValueAxis(this)),
        axisY1(new QValueAxis(this)),
        axisY2(new QValueAxis(this))
{
    currentIteration = 0;
    setupResidualPlot();
}

void ResidualPlotter::setupResidualPlot() {
    QFont titleFont("Arial",16,QFont::Bold);
    QColor titleColor("Qt::darkBlue");
    setTitle("Residual Curves");
    setTitleFont(titleFont);
    setTitleBrush(titleColor);

    addAxis(axisX,Qt::AlignBottom);
    addAxis(axisY1,Qt::AlignLeft);
    addAxis(axisY2,Qt::AlignRight);
    addSeries(series_con1);
    addSeries(series_con2);

    series_con1->attachAxis(axisX);
    series_con1->attachAxis(axisY1);
    series_con2->attachAxis(axisX);
    series_con2->attachAxis(axisY2);

    axisX->setTitleText("Iteration");
    axisY1->setTitleText("Conver_N-S");
    axisY2->setTitleText("Conver_Momum");

}

void ResidualPlotter::updateResidualPlot() {
    series_con1->append(currentIteration,currentIteration);
    currentIteration++;
    axisX->setRange(0,100);
    axisY1->setRange(0,100);

    this->update();
}