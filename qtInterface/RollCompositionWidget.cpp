#include <QLabel>

#include "../SWTraitRoll.h"

#include "RollCompositionWidget.h"

RollCompositionWidget::RollCompositionWidget(QWidget *parent): QWidget(parent), nTraitDieSides(4), nWildDieSides(6), nMod(0) {
    frame = new QFrame(this);
    frame->setFrameStyle(QFrame::Box);
    gridLayout = new QGridLayout(frame);
    gridLayout->addWidget(new QLabel("Trait Die:", frame), 1, 1);
    gridLayout->addWidget(new QLabel("Wild Die:", frame),2,1);
    gridLayout->addWidget(new QLabel("Modifier:", frame),3,1);
    gridLayout->addWidget(new QLabel("Rerolls:", frame),4,1);
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
    rerollsLineEdit = new QLineEdit(frame);
    gridLayout->addWidget(traitDieComboBox, 1, 2);
    gridLayout->addWidget(wildDieComboBox, 2, 2);
    gridLayout->addWidget(modifierLineEdit, 3, 2);
    gridLayout->addWidget(rerollsLineEdit, 4, 2);
    modifierLineEdit->setInputMask("###");
    rerollsLineEdit->setInputMask("###");

    QObject::connect(traitDieComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int newIndex) {this->traitDieChanged(newIndex);});
    QObject::connect(wildDieComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int newIndex) {this->wildDieChanged (newIndex);});
    QObject::connect(modifierLineEdit, QOverload<>::of(&QLineEdit::editingFinished),
            [this]() {this->modifierChanged();});
    QObject::connect(rerollsLineEdit, QOverload<>::of(&QLineEdit::editingFinished),
            [this]() {this->rerollsChanged();});

    resize(100,100);
}

RollCompositionWidget::~RollCompositionWidget(void) {
    delete traitDieComboBox;
    delete wildDieComboBox;
    delete modifierLineEdit;
    delete rerollsLineEdit;
    delete frame;
}


std::shared_ptr<StochasticObject> RollCompositionWidget::getRoll(void) const {

    return std::make_shared<SWTraitRoll>(nTraitDieSides, nWildDieSides, nMod, nRerolls);
}

void RollCompositionWidget::traitDieChanged(int newIndex) {
    nTraitDieSides = 2*(newIndex+2);
}


void RollCompositionWidget::wildDieChanged(int newIndex) {
    nWildDieSides = 2*(newIndex+2);
}

void RollCompositionWidget::modifierChanged(void) {
    nMod = modifierLineEdit->text().toInt();
}

void RollCompositionWidget::rerollsChanged(void) {
    nMod = rerollsLineEdit->text().toInt();
}
