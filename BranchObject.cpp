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
#include <iostream>
#include <limits>
#include <algorithm>

#include "BranchObject.h"

Branch::Branch(const std::shared_ptr<StochasticObject>& pResult_, double dRangeLower_):
        pResult(pResult_), dRangeLower(dRangeLower_)
{}

double Branch::distributionFunction(double dX) const {
    return pResult->distributionFunction(dX);
}

double Branch::getMinimum(void) const {
    return pResult->getMinimum();
}

bool Branch::operator<(const Branch& other) const {
    return dRangeLower<other.dRangeLower;
}

double Branch::getRangeLower(void) const {
    return dRangeLower;
}

BranchObject::BranchObject(const std::shared_ptr<StochasticObject>& pDecider_,
                           const std::shared_ptr<StochasticObject>& pDefault_) : 
    pDecider(pDecider_), pDefault(pDefault_), vBranches({}) {}

double BranchObject::distributionFunction(double dX) const {
    //std::cout << "dX"<<dX<<std::endl;
    double dProbability = .0;
    auto pLower = .0;//pDecider->distributionFunction(lastBoundary);
    double coveredPSpace = .0;
    for (auto &b: vBranches) {
        double newBoundary = b.getRangeLower();
        auto pUpper = pDecider->distributionFunction(newBoundary);
 //std::cout  << "pUpper: "<<pUpper<<" pLower: "<<pLower<<" boundary:"<<newBoundary<< " dF: "<<b.distributionFunction(dX)<<std::endl;
        dProbability += (pUpper-pLower)*b.distributionFunction(dX);
        coveredPSpace += (pUpper-pLower);
        pLower = pUpper;
    }
//    std::cout << "Covered P Space: "<< 1.-coveredPSpace <<  " dF: "<<pDefault->distributionFunction(dX)<<std::endl;

    dProbability += (1.-coveredPSpace)*pDefault->distributionFunction(dX);
    return dProbability;
}

double BranchObject::getMinimum(void) const {
    double dMinimum = std::numeric_limits<double>::infinity();
    for (auto &b: vBranches) {
        dMinimum = std::min(dMinimum, b.getMinimum());
    }
    dMinimum = std::min(dMinimum, pDefault->getMinimum());
    return dMinimum;
}
