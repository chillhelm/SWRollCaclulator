/*
Copyright 2021 Wilhelm Neubert
This file is part of SW Roll Calculator.

SW Roll Calculator is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

SW Roll Calculator is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with SW Roll Calculator.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <memory>

#include <qapplication.h>
#include <qpushbutton.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>

#include "RollCompositionWidget.h"

void fillBarSetFromStochasticObject(QtCharts::QBarSet *set, const std::shared_ptr<StochasticObject>& pStochasticObject) {
    set->remove(0, set->count());
    for(double x=0;x<5;++x) {
        *set << pStochasticObject->distributionFunction(x) - pStochasticObject->distributionFunction(x-1.);
    }
    *set << (1.-pStochasticObject->distributionFunction(4.));
}

void replot(QtCharts::QChart *chart, RollCompositionWidget* rcw1) {
    chart->removeAllSeries();
    QtCharts::QBarSet *set0 = new QtCharts::QBarSet("Roll 1");
    fillBarSetFromStochasticObject(set0, rcw1->getRoll());
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries;
    series->append(set0);
    chart->addSeries(series);
}

int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    RollCompositionWidget *rcw1 = new RollCompositionWidget;
    QtCharts::QBarSet *set0 = new QtCharts::QBarSet("Roll 1");

    fillBarSetFromStochasticObject(set0, rcw1->getRoll());

    QtCharts::QBarSeries *series = new QtCharts::QBarSeries;
    series->append(set0);

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("some title");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    QStringList categories;
    categories << "No Wound" << "1" << "2" << "3" << "4" << ">4";
    QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    //axisY->setRange(0,1);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QWidget window;
    QVBoxLayout *VBoxLayout = new QVBoxLayout(&window);
    QWidget RollSetupRow;
    QHBoxLayout *HBoxLayout = new QHBoxLayout(&RollSetupRow);
    HBoxLayout->addWidget(rcw1);
    QPushButton *plotButton = new QPushButton("Plot", &RollSetupRow);
    QObject::connect(plotButton, QOverload<bool>::of(&QPushButton::clicked), [rcw1, chart](bool){replot(chart,rcw1);});
    plotButton->resize(120,120);
    HBoxLayout->addWidget(plotButton);
    RollSetupRow.setMinimumHeight(120);
    VBoxLayout->addWidget(&RollSetupRow);
    VBoxLayout->addWidget(chartView);

    window.resize(900, 800);
    window.show();
    return a.exec();
}

