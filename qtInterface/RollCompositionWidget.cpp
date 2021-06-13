#include <QLabel>
#include <iostream>

#include "../AcingDie.h"
#include "../MaxConnector.h"
#include "../RaiseCounter.h"
#include "../FlatMod.h"
#include "../BranchObject.h"
#include "../ConstantObject.h"
#include "../AdderObject.h"
#include "../WoundCalculatorObject.h"

#include "RollCompositionWidget.h"

RollCompositionWidget::RollCompositionWidget(QWidget *parent): QWidget(parent), nTraitDieSides(4), nWildDieSides(6), nMod(0) {
    frame = new QFrame(this);
    frame->setFrameStyle(QFrame::Box);
    gridLayout = new QGridLayout(frame);
    gridLayout->addWidget(new QLabel("Trait Die:", frame), 1, 1);
    gridLayout->addWidget(new QLabel("Wild Die:", frame),2,1);
    gridLayout->addWidget(new QLabel("Modifier:", frame),3,1);
    traitDieComboBox = new QComboBox(frame);
    traitDieComboBox->addItem("d4");
    traitDieComboBox->addItem("d6");
    traitDieComboBox->addItem("d8");
    traitDieComboBox->addItem("d10");
    traitDieComboBox->addItem("d12");
    traitDieComboBox->setCurrentIndex(0);
    wildDieComboBox = new QComboBox(frame);
    wildDieComboBox->addItem("d4");
    wildDieComboBox->addItem("d6");
    wildDieComboBox->addItem("d8");
    wildDieComboBox->addItem("d10");
    wildDieComboBox->addItem("d12");
    wildDieComboBox->setCurrentIndex(1);
    modifierLineEdit = new QLineEdit(frame);
    gridLayout->addWidget(traitDieComboBox, 1, 2);
    gridLayout->addWidget(wildDieComboBox, 2, 2);
    gridLayout->addWidget(modifierLineEdit, 3, 2);
    modifierLineEdit->setInputMask("###");

    QObject::connect(traitDieComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int newIndex) {this->traitDieChanged(newIndex);});
    QObject::connect(wildDieComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int newIndex) {this->wildDieChanged (newIndex);});
    QObject::connect(modifierLineEdit, QOverload<>::of(&QLineEdit::editingFinished),
            [this]() {this->modifierChanged();});

    resize(100,100);
}

RollCompositionWidget::~RollCompositionWidget(void) {
    delete traitDieComboBox;
    delete wildDieComboBox;
    delete modifierLineEdit;
    delete frame;
}


std::shared_ptr<StochasticObject> RollCompositionWidget::getRoll(void) const {

    auto pTraitDie = std::make_shared<AcingDie>(nTraitDieSides);
    auto pWildDie = std::make_shared<AcingDie>(nWildDieSides);
    auto pAttackMaxConnector = std::make_shared<MaxConnector>(pTraitDie, pWildDie);
    auto pAttackModdedRoll = std::make_shared<FlatMod>(pAttackMaxConnector,nMod);
    auto pAttackRaiseCounter = std::make_shared<RaiseCounter>(pAttackModdedRoll);



    return pAttackRaiseCounter;
}

void RollCompositionWidget::traitDieChanged(int newIndex) {
    nTraitDieSides = 2*(newIndex+2);
    std::cout << "Trait Die Sides: "<<nTraitDieSides<<std::endl;
}


void RollCompositionWidget::wildDieChanged(int newIndex) {
    nWildDieSides = 2*(newIndex+2);
    std::cout << "Wild Die Sides: "<<nWildDieSides<<std::endl;
}

void RollCompositionWidget::modifierChanged(void) {
    nMod = modifierLineEdit->text().toInt();
}
