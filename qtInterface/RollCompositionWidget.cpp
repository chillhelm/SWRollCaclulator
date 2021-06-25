#include <QLabel>
#include <QResizeEvent>
#include <QShowEvent>

#include "../SWTraitRoll.h"

#include "RollCompositionWidget.h"

RollCompositionWidget::RollCompositionWidget(QWidget *parent): QFrame(parent), nTraitDieSides(4), nWildDieSides(6), nMod(0), nRerolls(0), nTargetNumber(4) {
    setFrameStyle(QFrame::Box);
    gridLayout = new QGridLayout(this);
    gridLayout->addWidget(new QLabel("Trait Die:", this), 1, 1);
    gridLayout->addWidget(new QLabel("Wild Die:", this),2,1);
    gridLayout->addWidget(new QLabel("Modifier:", this),3,1);
    gridLayout->addWidget(new QLabel("Rerolls:", this),4,1);
    gridLayout->addWidget(new QLabel("TN:", this),5,1);
    traitDieComboBox = new QComboBox(this);
    traitDieComboBox->addItem("d4");
    traitDieComboBox->addItem("d6");
    traitDieComboBox->addItem("d8");
    traitDieComboBox->addItem("d10");
    traitDieComboBox->addItem("d12");
    traitDieComboBox->setCurrentIndex(0);
    wildDieComboBox = new QComboBox(this);
    wildDieComboBox->addItem("d4");
    wildDieComboBox->addItem("d6");
    wildDieComboBox->addItem("d8");
    wildDieComboBox->addItem("d10");
    wildDieComboBox->addItem("d12");
    wildDieComboBox->setCurrentIndex(1);
    modifierSpinBox = new QSpinBox(this);
    rerollsSpinBox = new QSpinBox(this);
    targetNumberSpinBox = new QSpinBox(this);
    gridLayout->addWidget(traitDieComboBox, 1, 2);
    gridLayout->addWidget(wildDieComboBox, 2, 2);
    gridLayout->addWidget(modifierSpinBox, 3, 2);
    gridLayout->addWidget(rerollsSpinBox, 4, 2);
    gridLayout->addWidget(targetNumberSpinBox, 5, 2);

    modifierSpinBox->setValue(0);
    modifierSpinBox->setSingleStep(1);
    modifierSpinBox->setMinimum(-500);
    rerollsSpinBox->setValue(0);
    rerollsSpinBox->setSingleStep(1);
    rerollsSpinBox->setMinimum(0);
    targetNumberSpinBox->setMinimum(1);
    targetNumberSpinBox->setSingleStep(1);
    targetNumberSpinBox->setValue(4);

    deleteMeButton = new QPushButton("[X]",this);
    deleteMeButton->show();

    QObject::connect(traitDieComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int newIndex) {this->traitDieChanged(newIndex);});
    QObject::connect(wildDieComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int newIndex) {this->wildDieChanged (newIndex);});
    QObject::connect(modifierSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            [this](int val) {this->modifierChanged(val);});
    QObject::connect(rerollsSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            [this](int val) {this->rerollsChanged(val);});
    QObject::connect(targetNumberSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            [this](int val) {this->targetNumberChanged(val);});

    deleteMeButton->resize(15,15);
    auto newX=this->size().width()-15;
    deleteMeButton->move(newX, 0);
    resizeEvent(nullptr);
}

RollCompositionWidget::~RollCompositionWidget(void) {
    delete traitDieComboBox;
    delete wildDieComboBox;
    delete modifierSpinBox;
    delete rerollsSpinBox;

    delete deleteMeButton;
}


std::shared_ptr<StochasticObject> RollCompositionWidget::getRoll(void) const {

    return std::make_shared<SWTraitRoll>(nTraitDieSides, nWildDieSides, nMod-(nTargetNumber-4), nRerolls);
}

void RollCompositionWidget::traitDieChanged(int newIndex) {
    nTraitDieSides = 2*(newIndex+2);
}


void RollCompositionWidget::wildDieChanged(int newIndex) {
    nWildDieSides = 2*(newIndex+2);
}

void RollCompositionWidget::modifierChanged(int val) {
    nMod = val;
}

void RollCompositionWidget::rerollsChanged(int val) {
    nRerolls = val;
}

void RollCompositionWidget::targetNumberChanged(int val) {
    nTargetNumber = val;
}

void RollCompositionWidget::resizeEvent(QResizeEvent* ev) {
    auto newX=this->size().width()-15;
    deleteMeButton->move(newX, 0);
}


void RollCompositionWidget::showEvent(QShowEvent* ev) {
    auto newX=this->size().width()-15;
    deleteMeButton->move(newX, 0);
}
