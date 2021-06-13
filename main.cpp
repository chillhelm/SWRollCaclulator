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
#include "SWTraitRoll.h"

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
    SWTraitRoll fullTraitRoll(nDieSides1, nDieSides2, dMod);

    std::cout << "Probability of Critical Failure: "<<std::fixed << std::setprecision(2) << 100.*fullTraitRoll.distributionFunction(-1.)<< " %" << std::endl;
    std::cout << "Probability of Failure: "<<std::fixed << std::setprecision(2) <<  100.*fullTraitRoll.distributionFunction(.0)<<" %"<<std::endl;
    std::cout << resetiosflags(std::ios_base::floatfield);
    double lastProb = 1.;
    double x = 1.;
    while (lastProb>.01) {
        std::cout << "Probability of at least "<<std::noshowpos<<x<<" Successes & Raises:  ";
        std::cout << std::fixed << std::setprecision(2) << 100.0*(1.-fullTraitRoll.distributionFunction(x-1.)) << "%"<<std::endl;
        std::cout << resetiosflags(std::ios_base::floatfield);
        lastProb = (1.-fullTraitRoll.distributionFunction(x-1.));
        ++x;
    }

    return 0;
}
