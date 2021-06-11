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
#ifndef __ACINGDIE_H__
#define __ACINGDIE_H__

#include "StochasticObject.h"

class AcingDie: public StochasticObject {
    private:
        unsigned int nSides;
    public:
        AcingDie(unsigned int _nSides);
        virtual ~AcingDie(void) = default;
        virtual double massFunction(double x) const;
        virtual double distributionFunction(double x) const;
        virtual double getMinimum(void) const;
};
#endif
