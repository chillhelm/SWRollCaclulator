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
#include <iomanip>
#include <memory>
#include <cmath>
#include "AcingDie.h"
#include "MaxConnector.h"
#include "RaiseCounter.h"
#include "FlatMod.h"

int main(int argc, char* argv[]) {
    if(argc == 1) {
        std::cout << "Usage:\n"<<argv[0]<<" TraitDie [Modifier] [WildDie]" << std::endl;
        return 1;
    }
    unsigned int nDieSides1{4},nDieSides2{6};;
    double dMod = .0;
    if(argc>1) {
        nDieSides1 = std::stoul(std::string{argv[1]});
    }
    if(argc>2) {
        dMod = std::stod(std::string{argv[2]});
    }
    if(argc>3) {
        nDieSides2 = std::stod(std::string{argv[3]});
    }
    if (nDieSides1 <= 1) {
        std::cout << "Please give a positive, integer number greater than 1 as first parameter." << std::endl;
        return 1;
    }
    auto pDie1 = std::make_shared<AcingDie>(nDieSides1);
    auto pDie2 = std::make_shared<AcingDie>(nDieSides2);
    auto pMaxConnector = std::make_shared<MaxConnector>(pDie1, pDie2);
    auto pModdedRoll = std::make_shared<FlatMod>(pMaxConnector,dMod);
    auto pRaiseCounter = std::make_shared<RaiseCounter>(pModdedRoll);
    auto dCritFailProb = pMaxConnector->distributionFunction(1.0);

    std::cout << "Probability of Critical Failure: "<<std::fixed << std::setprecision(2) <<  100.0*dCritFailProb<<"%"<<std::endl;
    std::cout << "Probability of Failure: "<<std::fixed << std::setprecision(2) <<  100.0*(pRaiseCounter->distributionFunction(0.) + (dMod>=3.0? dCritFailProb : .0))<<"%"<<std::endl;
    std::cout << resetiosflags(std::ios_base::floatfield);
    double lastProb = 1.;
    double x = 1.;
    while (lastProb>.01) {
        std::cout << "Probability of at least "<<std::noshowpos<<x<<" Successes & Raises:  ";
        if(dMod+1.>=4.*x)
            std::cout << std::fixed << std::setprecision(2) <<  100.0*(1.0 - pRaiseCounter->distributionFunction(x-1.) - dCritFailProb)<<"%"<<std::endl;
        else
            std::cout <<  std::fixed << std::setprecision(2) <<  100.0*(1.0 - pRaiseCounter->distributionFunction(x-1.))<<"%" <<std::endl;
        std::cout << resetiosflags(std::ios_base::floatfield);
        lastProb = 1.0 - pRaiseCounter->distributionFunction(x - 1.) - (dMod+1.>=4.*x? dCritFailProb : .0);
        ++x;
    }

    return 0;
}
