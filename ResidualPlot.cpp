#include "ResidualPlot.h"

ResidualPlotter::ResidualPlotter(QWidget* parent):
        QChart(),series_con1(new QLineSeries(this)),
        series_con2(new QLineSeries(this)),
        axisX(new QValueAxis(this)),
        axisY1(new QValueAxis(this)),
        axisY2(new QValueAxis(this))
{
    //currentIteration = 0;
    minCon1 = std::numeric_limits<double>::max();
    maxCon1 = std::numeric_limits<double>::min();
    minCon2 = std::numeric_limits<double>::max();
    maxCon2 = std::numeric_limits<double>::min();
    maxIteration = 0;
    setupResidualPlot();
}

void ResidualPlotter::setupResidualPlot() {
    QFont titleFont("Arial",16,QFont::Bold);
    QColor titleColor(Qt::darkBlue);
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

void ResidualPlotter::updateResidualPlot(const int& iteration, const double& convergence1,
                                         const double& convergence2)  {



    series_con1->append(iteration,convergence1);
    series_con2->append(iteration,convergence2);


    maxIteration = std::max(maxIteration,iteration);
    maxCon1 = std::max(maxCon1,convergence1);
    maxCon2 = std::max(maxCon2,convergence2);
    minCon1 = std::min(minCon1,convergence1);
    minCon2 = std::min(minCon2,convergence2);
    axisX->setRange(0,maxIteration);
    axisY1->setRange(minCon1,maxCon1);  
    axisY2->setRange(minCon2,maxCon2);

    this->update();
}