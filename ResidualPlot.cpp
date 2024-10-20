#include "ResidualPlot.h"

ResidualPlotter::ResidualPlotter(QWidget* parent):
        QChart(),series_con1(new QLineSeries(this)),
        series_con2(new QLineSeries(this)),
        axisX(new QValueAxis(this)),
        axisY1(new QValueAxis(this)),
        axisY2(new QValueAxis(this))
{
    //currentIteration = 0;
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

void ResidualPlotter::updateResidualPlot(const QVector<double> &iteration, const QVector<double> &convergence1,
                                         const QVector<double> &convergence2)  {

    series_con1->clear();
    series_con2->clear();

    for(int i =0; i<iteration.size();++i){
        series_con1->append(iteration[i],convergence1[i]);
        series_con2->append(iteration[i],convergence2[i]);
    }

    if(!iteration.isEmpty()){
        int maxIter = *std::max_element(iteration.begin(), iteration.end());
        double maxCon1 = *std::max_element(convergence1.begin(), convergence1.end());
        double maxCon2 = *std::max_element(convergence2.begin(), convergence2.end());

        axisX->setRange(0,maxIter+4);
    }
    axisY1->setRange(-8.2,-7);
    axisY2->setRange(-11.5,-10.5);

    this->update();
}