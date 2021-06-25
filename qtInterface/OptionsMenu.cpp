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

#include "OptionsMenu.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>

OptionsMenu::OptionsMenu(MainQtWindow &optionsTarget_, QWidget *parent): QWidget(parent), optionsTarget(optionsTarget_) {
    setWindowTitle("SW Roll Calculator Options");
    setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Dialog);

    QGridLayout *GridLayout = new QGridLayout(this);

    // number of raises to display
    QLabel *raiseNumberLabel = new QLabel("Number of Raises to Plot:", this);
    GridLayout->addWidget(raiseNumberLabel,1,1);
    QSpinBox *raiseNumber = new QSpinBox(this);
    raiseNumber->setValue(4);
    raiseNumber->setSingleStep(1);
    raiseNumber->setMinimum(0);
    GridLayout->addWidget(raiseNumber,1,2);
    QObject::connect(raiseNumber, QOverload<int>::of(&QSpinBox::valueChanged),
            [this](int val) {this->raiseNumberChanged(val);});

    // at least or exact successes
    QLabel *probabilityDisplayModeLabel = new QLabel("Success Probabilities:", this);
    GridLayout->addWidget(probabilityDisplayModeLabel,2,1);
    QComboBox *probDisplayModeComboBox = new QComboBox(this);
    probDisplayModeComboBox->addItem("Probability of EXACTLY n Successes/Raises");
    probDisplayModeComboBox->addItem("Probability of AT LEAST n Successes/Raises");
    GridLayout->addWidget(probDisplayModeComboBox,2,2);
    QObject::connect(probDisplayModeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int newIndex) {this->probDisplayModeComboBoxChanged (newIndex);});

    // OK/close button
    QPushButton* closeButton = new QPushButton("Done", this);
    GridLayout->addWidget(closeButton,3,2);
    QObject::connect(closeButton, QOverload<bool>::of(&QPushButton::clicked), [this](bool){this->close();});
}

OptionsMenu::~OptionsMenu(void) {
}

void OptionsMenu::raiseNumberChanged(int val) {
    optionsTarget.setPlotRaiseNumber(val);
}

void OptionsMenu::probDisplayModeComboBoxChanged(int newIndex) {
    optionsTarget.setDisplayExactProbabilities(newIndex==0);
}

