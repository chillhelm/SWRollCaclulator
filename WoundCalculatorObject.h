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
#ifndef __WOUNDCALCULATOROBJECT_H__
#define __WOUNDCALCULATOROBJECT_H__

#include <memory>
#include "StochasticObject.h"

class WoundCalculatorObject: public StochasticObject {
    private:
        std::shared_ptr<StochasticObject> pDamage;
        double dToughness;
        bool bShaken;
    public:
        WoundCalculatorObject(const std::shared_ptr<StochasticObject>& pDamage, double dToughness, bool bShaken);
        virtual ~WoundCalculatorObject(void) = default;

        virtual double distributionFunction(double dX_) const;
        virtual double getMinimum(void) const;

        double getToughness(void) const {return dToughness;};
        void setToughness(double dToughness_) {dToughness=dToughness_;};

        bool isShaken(void) const {return bShaken;};
        void setShaken(bool bShaken_) {bShaken = bShaken_;};
};

#endif
