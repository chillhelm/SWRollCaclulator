#ifndef __ROLLCOMPOSITIONWIDGET_H__
#define __ROLLCOMPOSITIONWIDGET_H__

#include <QWidget>
#include <QGridLayout>
#include <QFrame>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
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

        int nTraitDieSides;
        int nWildDieSides;
        int nMod;
        int nRerolls;

    public:
        RollCompositionWidget(QWidget *parent = nullptr);
        virtual ~RollCompositionWidget(void);

        std::shared_ptr<StochasticObject> getRoll(void) const;

        void traitDieChanged(int newIndex);
        void wildDieChanged(int newIndex);
        void modifierChanged(int val);
        void rerollsChanged(int val);
};

#endif

