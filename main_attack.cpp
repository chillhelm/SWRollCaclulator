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
#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <memory>
#include <cmath>
#include "AcingDie.h"
#include "MaxConnector.h"
#include "RaiseCounter.h"
#include "FlatMod.h"
#include "BranchObject.h"
#include "ConstantObject.h"
#include "AdderObject.h"
#include "WoundCalculatorObject.h"


int main(int argc, char* argv[]) {
    unsigned int nDieSides1 = 4;
    unsigned int nDieSides2 = 6;

    unsigned int nDmgDieSides1 = 8;
    unsigned int nDmgDieSides2 = 6;
    unsigned int nDmgDieRaise = 6;
    double dMod = 0.;

    auto pAttackDie1 = std::make_shared<AcingDie>(nDieSides1);
    auto pAttackDie2 = std::make_shared<AcingDie>(nDieSides2);
    auto pAttackMaxConnector = std::make_shared<MaxConnector>(pAttackDie1, pAttackDie2);
    auto pAttackModdedRoll = std::make_shared<FlatMod>(pAttackMaxConnector,dMod);
    auto pAttackRaiseCounter = std::make_shared<RaiseCounter>(pAttackModdedRoll);


    auto pDmgDie1 = std::make_shared<AcingDie>(nDmgDieSides1);
    auto pDmgDie2 = std::make_shared<AcingDie>(nDmgDieSides2);
    auto pDmgDieRaise = std::make_shared<AcingDie>(nDmgDieRaise);

    auto pTotalDmg = std::make_shared<AdderObject>(pDmgDie1, pDmgDie2);
    auto pTotalRaiseDmg = std::make_shared<AdderObject>(pTotalDmg, pDmgDieRaise);
    auto pNoHitDmg = std::make_shared<ConstantObject>(.0);

    bool bShaken = true;
    auto pWoundCalculator = std::make_shared<WoundCalculatorObject>(pTotalDmg, 4, bShaken);
    auto pWoundAfterRaiseCalculator = std::make_shared<WoundCalculatorObject>(pTotalRaiseDmg, 4, bShaken);

    auto branchObject = std::make_shared<BranchObject>(pAttackRaiseCounter, pWoundAfterRaiseCalculator);

    branchObject->vBranches.insert(Branch(pNoHitDmg, 0.));
    branchObject->vBranches.insert(Branch(pWoundCalculator, 1.));
    double total = .0;
    for (double x=0; x<5;++x) {
        auto p1=branchObject->distributionFunction(x);
        auto p2=branchObject->distributionFunction(x-1.);
        auto p = p1-p2;
        std::cout << x << "    "<<p1-p2<<std::endl;
        total +=p;
    }
    std::cout << "Total: "<<total << std::endl;
    std::cout << "   >4: "<<1.-branchObject->distributionFunction(4.)<<std::endl;
}


