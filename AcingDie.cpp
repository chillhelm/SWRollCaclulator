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
#include "AcingDie.h"

#include <string>
#include <limits>
#include <cmath>

AcingDie::AcingDie(unsigned int _nSides): nSides(_nSides) {
    if (nSides==0)
        throw std::string{"AcingDie must have >0 sides."};
}

double AcingDie::massFunction(double dX) const {
    if (dX<.0)
        return .0;

    double dIntegerPartOfX{.0};
    std::modf(dX, &dIntegerPartOfX);
    if(std::fmod(dIntegerPartOfX,(double)nSides) == 0.) {
        return .0;
    }
    double dAces = std::floor(dIntegerPartOfX/nSides);
    return std::pow(1.0/double(nSides), double(dAces)+1.0);
}

double AcingDie::distributionFunction(double dX) const {
    if (dX<1.)
        return .0;
    double dIntegerPartOfX{.0};
    std::modf(dX, &dIntegerPartOfX);
    double dAces = std::floor(dIntegerPartOfX/nSides);
    double dDist = nSides*(dAces+1)-dIntegerPartOfX;
    return 1.0 - (std::pow(1.0/double(nSides), double(dAces)) * double(dDist) / double(nSides));
}

double AcingDie::getMinimum(void) const {
    return 1.;
}
