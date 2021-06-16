#ifndef __ROLLCOMPOSITIONWIDGET_H__
#define __ROLLCOMPOSITIONWIDGET_H__

#include <QWidget>
#include <QGridLayout>
#include <QFrame>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <memory>
#include "../StochasticObject.h"


class RollCompositionWidget: public QWidget {
    Q_OBJECT
    private:
        QFrame *frame;
        QGridLayout *gridLayout;
        QComboBox *traitDieComboBox;
        QComboBox *wildDieComboBox;
        QSpinBox *modifierSpinBox;
        QSpinBox *rerollsSpinBox;
        QPushButton *deleteMeButton;

        int nTraitDieSides;
        int nWildDieSides;
        int nMod;
        int nRerolls;

    protected:
        void resizeEvent(QResizeEvent *ev);
        void showEvent(QShowEvent *ev);
    public:
        RollCompositionWidget(QWidget *parent = nullptr);
        virtual ~RollCompositionWidget(void);

        std::shared_ptr<StochasticObject> getRoll(void) const;

        void traitDieChanged(int newIndex);
        void wildDieChanged(int newIndex);
        void modifierChanged(int val);
        void rerollsChanged(int val);

        int getTraitDieSides() {return nTraitDieSides;};
        int getWildDieSides() {return nWildDieSides;};
        int getMod() {return nMod;};
        int getRerolls() {return nRerolls;};

        QPushButton *getDeleteMeButton(void) {return deleteMeButton;};
};

#endif

