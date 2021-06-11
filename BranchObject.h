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
#ifndef __BRANCHOBJECT_H__
#define __BRANCHOBJECT_H__

#include "StochasticObject.h"
#include <memory>
#include <set>

class Branch: public StochasticObject {
    private:
        std::shared_ptr<StochasticObject> pResult;
        double dRangeLower;
    public:
        Branch(const std::shared_ptr<StochasticObject>& pResult_, double dRangeLower_);
        virtual ~Branch(void) = default;
        virtual double distributionFunction(double) const;
        virtual double getMinimum(void) const;

        double getRangeLower(void) const;
        bool operator<(const Branch& other) const;
};

class BranchObject: public StochasticObject {
    private:
        std::shared_ptr<StochasticObject> pDecider;
        std::shared_ptr<StochasticObject> pDefault;
    public:
        BranchObject(const std::shared_ptr<StochasticObject>& pDecider_, const std::shared_ptr<StochasticObject>& pDefault_);
        virtual ~BranchObject(void) = default;
        virtual double distributionFunction(double) const;
        virtual double getMinimum(void) const;

        std::set<Branch> vBranches;
};

#endif
