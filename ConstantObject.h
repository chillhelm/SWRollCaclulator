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
#ifndef __CONSTANTOBJECT_H__
#define __CONSTANTOBJECT_H__

#include "StochasticObject.h"

class ConstantObject: public StochasticObject {
    private:
        double dResult;
    public:
        ConstantObject(double dResult_=0): dResult(dResult_) {};
        virtual ~ConstantObject(void) = default;

        virtual double distributionFunction(double dX) const {
            return (dX>=dResult?1.0:0.0);
        };
        virtual double getMinimum(void) const {
            return dResult;
        };

        void setResult(double dResult_) {dResult=dResult_;};
        double getResult(void) {return dResult;};
};

#endif
