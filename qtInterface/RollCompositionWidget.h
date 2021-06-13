#include <QWidget>
#include <QGridLayout>
#include <QFrame>
#include <QComboBox>
#include <QLineEdit>
#include <memory>
#include "../StochasticObject.h"

class RollCompositionWidget: public QWidget {
    Q_OBJECT
    private:
        QFrame *frame;
        QGridLayout *gridLayout;
        QComboBox *traitDieComboBox;
        QComboBox *wildDieComboBox;
        QLineEdit *modifierLineEdit;

        int nTraitDieSides;
        int nWildDieSides;
        int nMod;

    public:
        RollCompositionWidget(QWidget *parent = nullptr);
        virtual ~RollCompositionWidget(void);

        std::shared_ptr<StochasticObject> getRoll(void) const;

        void traitDieChanged(int newIndex);
        void wildDieChanged(int newIndex);
        void modifierChanged(void);
};
