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

#include "SWTraitRoll.h"
#include "AcingDie.h"
#include "MaxConnector.h"
#include "FlatMod.h"
#include "RaiseCounter.h"

SWTraitRoll::SWTraitRoll(unsigned int nTraitDieSides_, unsigned int nWildDieSides_, int nMod_): nTraitDieSides(nTraitDieSides_), nWildDieSides(nWildDieSides_), nMod(nMod_) {
}

double SWTraitRoll::distributionFunction(double dX) const {
    if(dX<-1.)
        return .0;
    auto traitDie = std::make_shared<AcingDie>(nTraitDieSides);
    auto wildDie = std::make_shared<AcingDie>(nWildDieSides);
    auto rollResult = std::make_shared<MaxConnector>(traitDie, wildDie);
    if((dX<.0) || ((dX<1.) && (nMod>=3))) // Probability of crit fail
        return rollResult->distributionFunction(1.);
    auto pModdedRoll = std::make_shared<FlatMod>(rollResult,nMod);
    RaiseCounter raiseCounter(pModdedRoll);

    return raiseCounter.distributionFunction(dX);
}

