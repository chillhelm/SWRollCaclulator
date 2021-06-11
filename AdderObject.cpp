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
#include "AdderObject.h"

AdderObject::AdderObject(const std::shared_ptr<StochasticObject>& pLeftSummand_,const std::shared_ptr<StochasticObject>& pRightSummand_):
    pLeftSummand(pLeftSummand_), pRightSummand(pRightSummand_) {}

double AdderObject::distributionFunction(double dX) const{
    double dProbability = .0;
    for (double dZ = pLeftSummand->getMinimum(); dZ<=dX; ++dZ) {
        dProbability += (pLeftSummand->distributionFunction(dZ)-pLeftSummand->distributionFunction(dZ-1.))*pRightSummand->distributionFunction(dX-dZ);
    }
    return dProbability;
}

double AdderObject::getMinimum(void) const {
    return pLeftSummand->getMinimum() + pRightSummand->getMinimum();
}

