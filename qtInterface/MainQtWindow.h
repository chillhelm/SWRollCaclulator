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
#ifndef __MAINQTWINDOW_H__
#define __MAINQTWINDOW_H__

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
#include "InfoWindow.h"

class MainQtWindow: public QWidget {
    Q_OBJECT;
    private:
        QtCharts::QChart *chart;
        QtCharts::QBarCategoryAxis *axisX;
        QtCharts::QValueAxis *axisY;
        QtCharts::QChartView *chartView;
        QVBoxLayout *VBoxLayout;
        QHBoxLayout *HBoxLayout;
        QWidget *RollSetupRow;

        double fillBarSetFromStochasticObject(QtCharts::QBarSet& set, const std::shared_ptr<StochasticObject>& pStochasticObject);
        int nRCWCount;

        void hoveredBar(bool status, int index, QtCharts::QBarSet* set);
        void createMenuBar(void);
    public:
        MainQtWindow(QWidget *parent_=nullptr);
        ~MainQtWindow(void);

        void updateChart(void);
        void addRCW(void);
        void exportCSV(void);
        void exportPNG(void);
};

#endif

