#include "ResidualPlot.h"

ResidualPlotter::ResidualPlotter(QWidget* parent):
        QChart(),series_con1(new QLineSeries(this)),
        series_con2(new QLineSeries(this)),
        axisX(new QValueAxis(this)),
        axisY1(new QValueAxis(this)),
        axisY2(new QValueAxis(this))
{
    //currentIteration = 0;
//    minCon1 = std::numeric_limits<double>::max();
//    maxCon1 = std::numeric_limits<double>::lowest();
//    minCon2 = std::numeric_limits<double>::max();
//    maxCon2 = std::numeric_limits<double>::lowest();
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

    axisX->setGridLineVisible(false);
    axisY1->setGridLineVisible(true);
    axisY2->setGridLineVisible(true);
}

void ResidualPlotter::updateResidualPlot(const int& iteration, const double& convergence1,
                                         const double& convergence2)  {



    series_con1->append(iteration, convergence1);
    series_con2->append(iteration, convergence2);

    // 更新范围
    maxIteration = std::max(maxIteration, iteration);

    // 对于第一个数据点，初始化最大最小值
    if (series_con1->count() == 1) {
        maxCon1 = minCon1 = convergence1;
        maxCon2 = minCon2 = convergence2;
    } else {
        maxCon1 = std::max(maxCon1, convergence1);
        maxCon2 = std::max(maxCon2, convergence2);
        minCon1 = std::min(minCon1, convergence1);
        minCon2 = std::min(minCon2, convergence2);
    }

    double range1 = maxCon1 - minCon1;
    double range2 = maxCon2 - minCon2;

    double margin1 = range1 * 0.2;
    double margin2 = range2 * 0.2;

    axisX->setRange(0, maxIteration + 5);
    axisY1->setRange(minCon1 - margin1, maxCon1 + margin1);
    axisY2->setRange(minCon2 - margin2, maxCon2 + margin2);

    axisY1->setLabelFormat("%.1f");
    axisY2->setLabelFormat("%.1f");


    this->update();
}