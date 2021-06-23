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
#include "MaxConnector.h"
#include <algorithm>

MaxConnector::MaxConnector(const std::shared_ptr<StochasticObject> &pObject1_, const std::shared_ptr<StochasticObject> &pObject2_) : 
                pObject1(pObject1_), pObject2(pObject2_) {
}

double MaxConnector::distributionFunction(double x) const {
    auto pObject1TooBig = 1.0 - pObject1->distributionFunction(x);
    auto pObject2TooBig = 1.0 - pObject2->distributionFunction(x);

    return (1.0 - pObject1TooBig)*(1.0 - pObject2TooBig);
}

double MaxConnector::getMinimum(void) const {
    return std::max(pObject1->getMinimum(), pObject2->getMinimum());
}

