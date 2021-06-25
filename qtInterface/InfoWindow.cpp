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
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "InfoWindow.h"

InfoWindow::InfoWindow(QWidget *parent): QWidget(parent) {
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle("About SWRollCalculator");
    setWindowFlags(Qt::FramelessWindowHint);

    QVBoxLayout *VBoxLayout = new QVBoxLayout(this);

    auto titleLabel = std::make_unique<QLabel>("<h1>SWRollCalculator v.1</h1>");
    titleLabel->setTextFormat(Qt::RichText);
    VBoxLayout->addWidget(titleLabel.release(),0, Qt::AlignHCenter);
    VBoxLayout->addWidget(new QLabel("Copyright 2021 Wilhelm Neubert"), 0, Qt::AlignHCenter);

    auto licenseLabel = std::make_unique<QLabel>("<center>This product is released under GNU General Public License version 3.</center>");
    licenseLabel->setTextFormat(Qt::RichText);
    licenseLabel->setWordWrap(true);
    VBoxLayout->addWidget(licenseLabel.release());

    auto sourceCodeLabel = std::make_unique<QLabel>("<center>You can find the Source Code and the text of the license at\
            <a href=\"https://github.com/chillhelm/SWRollCalculator\">github.com/chillhelm/SWRollCalculator</a>.</center>");
    sourceCodeLabel->setTextFormat(Qt::RichText);
    sourceCodeLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    sourceCodeLabel->setOpenExternalLinks(true);
    sourceCodeLabel->setWordWrap(true);
    VBoxLayout->addWidget(sourceCodeLabel.release());

    auto qtCreditLabel = std::make_unique<QLabel>("<center>This program uses the Qt library. Visit them at <a href=\"https://www.qt.io/\">qt.io</a>.</center>");
    qtCreditLabel->setTextFormat(Qt::RichText);
    qtCreditLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    qtCreditLabel->setOpenExternalLinks(true);
    qtCreditLabel->setWordWrap(true);
    VBoxLayout->addWidget(qtCreditLabel.release());

    QPushButton* closeButton = new QPushButton("OK");
    VBoxLayout->addWidget(closeButton,0,Qt::AlignHCenter);
    QObject::connect(closeButton, QOverload<bool>::of(&QPushButton::clicked), [this](bool){this->close();});
}


InfoWindow::~InfoWindow(void) {
}

