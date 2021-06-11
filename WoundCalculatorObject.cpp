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
#include <cmath>

#include "FlatMod.h"
#include "RaiseCounter.h"

#include "WoundCalculatorObject.h"


WoundCalculatorObject::WoundCalculatorObject(const std::shared_ptr<StochasticObject>& pDamage_, double dToughness_, bool bShaken_) :
        pDamage(pDamage_), dToughness(dToughness_), bShaken(bShaken_) {}

double WoundCalculatorObject::distributionFunction(double dX) const {
    if(dX<.0)
        return .0;
    double dIntegerPartOfX{.0};
    std::modf(dX, &dIntegerPartOfX);

    auto normalizedRoll = std::make_shared<FlatMod>(pDamage, 4.0-dToughness);
    auto raiseCounter = std::make_shared<RaiseCounter>(normalizedRoll);
    if((!bShaken) || (dX>=2.)) {
        return raiseCounter->distributionFunction(dX+1.);
    } else {
        if(dX<1.) {
            return normalizedRoll->distributionFunction(3.);
        }
        else {
            return normalizedRoll->distributionFunction(11.);
        }
    }
    return .0;
}

double WoundCalculatorObject::getMinimum(void) const {
    return .0;
}

