#include <QLabel>
#include <QResizeEvent>

#include "../SWTraitRoll.h"

#include "RollCompositionWidget.h"

RollCompositionWidget::RollCompositionWidget(QWidget *parent): QWidget(parent), nTraitDieSides(4), nWildDieSides(6), nMod(0), nRerolls(0) {
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
    modifierSpinBox = new QSpinBox(frame);
    rerollsSpinBox = new QSpinBox(frame);
    gridLayout->addWidget(traitDieComboBox, 1, 2);
    gridLayout->addWidget(wildDieComboBox, 2, 2);
    gridLayout->addWidget(modifierSpinBox, 3, 2);
    gridLayout->addWidget(rerollsSpinBox, 4, 2);

    modifierSpinBox->setValue(0);
    modifierSpinBox->setSingleStep(1);
    rerollsSpinBox->setValue(0);
    rerollsSpinBox->setSingleStep(1);
    rerollsSpinBox->setMinimum(0);

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

    resize(100,100);
    deleteMeButton->resize(15,15);
    auto newX=frame->size().width()+frame->pos().x()-15;
    deleteMeButton->move(newX, frame->pos().y());
}

RollCompositionWidget::~RollCompositionWidget(void) {
    delete traitDieComboBox;
    delete wildDieComboBox;
    delete modifierSpinBox;
    delete rerollsSpinBox;
    delete frame;

    delete deleteMeButton;
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

void RollCompositionWidget::modifierChanged(int val) {
    nMod = val;
}

void RollCompositionWidget::rerollsChanged(int val) {
    nRerolls = val;
}

void RollCompositionWidget::resizeEvent(QResizeEvent* ev) {
    auto newX=frame->size().width()+frame->pos().x()-15;
    deleteMeButton->move(newX, frame->pos().y());
}

