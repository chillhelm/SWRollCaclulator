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

#include <memory>
#include <cmath>

#include "SWTraitRoll.h"
#include "AcingDie.h"
#include "MaxConnector.h"
#include "FlatMod.h"
#include "RaiseCounter.h"

namespace {
    unsigned int NChooseK(unsigned int N, unsigned int K) {
        if(K==0) return 1;
        unsigned int res=N;
        for(unsigned int i=1;i<=K;++i) {
            res*=N-i;
        }
        for(unsigned int i=1;i<=K;++i) {
            res/=i;
        }
        return res;
    }
}

SWTraitRoll::SWTraitRoll(unsigned int nTraitDieSides_, unsigned int nWildDieSides_, int nMod_, unsigned int nTraitDiceCount_, unsigned int nRerolls_): nTraitDieSides(nTraitDieSides_), nWildDieSides(nWildDieSides_),nTraitDiceCount(nTraitDiceCount_), nRerolls(nRerolls_), nMod(nMod_) {
}

double SWTraitRoll::distributionFunction(double dX) const {
    if(dX<-1.)
        return .0;
    auto traitDie = std::make_shared<AcingDie>(nTraitDieSides);
    auto wildDie = std::make_shared<AcingDie>(nWildDieSides);
    auto rollResult = std::make_shared<MaxConnector>(traitDie, wildDie);
    for(unsigned int nTraitDieIndex = 1; nTraitDieIndex<nTraitDiceCount; ++i) {
        rollResult = std::make_shared<MaxConnector>(rollResult, traitDie);
    }

    double anyCritFailProbability = 1.-std::pow(1.-rollResult->distributionFunction(1.), nRerolls+1.);
    double individualCritFailProbability = rollResult->distributionFunction(1.);

    if((dX<.0) || ((dX<1.) && (nMod>=2))) // Probability of crit fail
        return anyCritFailProbability;
    /*if(dX<1.)
        return 1.-std::pow(rollResult->distributionFunction(4.-nMod),nRerolls+1);*/

    double dIntegerPartOfX = std::floor(dX);
    double rollLimit = 4.*dIntegerPartOfX-nMod+3.;
    if(rollLimit<2.)
        return anyCritFailProbability;

    double individualNotTooLarge = rollResult->distributionFunction(rollLimit)-rollResult->distributionFunction(1.);

    
    double probability = 1.;
    for (unsigned int i=0; i<=nRerolls; ++i) {
       probability = individualCritFailProbability + individualNotTooLarge*probability + (1.-individualNotTooLarge - individualCritFailProbability)*(1.-std::pow(1.-rollResult->distributionFunction(1.),i));
    }

    //double probability = critFailProbability + std::pow(rollResult->distributionFunction(4.*dIntegerPartOfX-nMod)-rollResult->distributionFunction(1.),nRerolls);
    return probability;
}

double nHighestDieProbabilityDistributionFunction(double dX, unsigned n) {

    if(n>nTraitDiceCount+1) return (dX>=0?1.:.0); // the 4th highest die out of 3 dice is defined to be rolling a 0

    auto traitDie = std::make_shared<AcingDie>(nTraitDieSides);
    auto wildDie = std::make_shared<AcingDie>(nWildDieSides);
    /* Pr[n highest out of K Trait Die and one WD is <= dX] = 1.-Pr[n or more Dice > dX] = 1.-(Pr[WD>dX]Pr[n-1 or more TD >dX]+Pr[Wd<=dX]Pr[n or more TD>dX])
     */
    double probNOrMoreTDTooLarge = .0;
    for(unsigned int i = n; i<=nTraitDiceCount; ++i) {
        probNOrMoreTDTooLarge += NChooseK(nTraitDiceCount, i)*std::pow(1.-traitDie->distributionFunction(dX),i)*std::pow(traitDie->distributionFunction(dX),nTraitDiceCount-i);
    }
    double probN_1OrMoreTDTooLarge = probNOrMoreTDTooLarge + 
        NChooseK(nTraitDiceCount, n-1)*std::pow(1.-traitDie->distributionFunction(dX),n-1)*std::pow(traitDie->distributionFunction(dX),nTraitDiceCount-(n-1));
    double 
    return 1. - (1.-wildDie->distributionFunction(dX))*probN_1OrMoreTDTooLarge - wildDie->distributionFunction(dX)*probNOrMoreTDTooLarge;
}

/* computes Pr[index highest die of this roll has successes/failures <= dX]
 * (given nRerolls many free rerolls ofc)
 */ 
double SWTraitRoll::distributionFunction(double dX, unsigned int index) const {
    if(dX<-1.)
        return .0;
    auto traitDie = std::make_shared<AcingDie>(nTraitDieSides);
    auto wildDie = std::make_shared<AcingDie>(nWildDieSides);
    auto rollResult = std::make_shared<MaxConnector>(traitDie, wildDie);
    for(unsigned int nTraitDieIndex = 1; nTraitDieIndex<nTraitDiceCount; ++i) {
        rollResult = std::make_shared<MaxConnector>(rollResult, traitDie);
    }

    unsigned int nTraitDieOnesRequiredForCritFail = (nTraitDiceCount+1)/2;
    double individualCritFailProbability = .0;
    for(unsigned int i=nTraitDieOnesRequiredForCritFail;i<=nTraitDiceCount; ++i) {
        individaulCritFailProbability += nChooseK(nTraitDiceCount, i)*std::pow(traitDie->distributionFunction(1.),i)*std::pow(1.-traitDie->distributionFunction(1.),nTraitDiceCount-i);
    }
    individualCritFailProbability *= wildDie->distributionFunction(1.);
    double anyCritFailProbability = 1.-std::pow(1.-individualCritFailProbability, nRerolls+1.);

    if((dX<.0) || ((index==1) && (dX<1.) && (nMod>=2))) // Probability of crit fail
        return anyCritFailProbability;
    /*if(dX<1.)
        return 1.-std::pow(rollResult->distributionFunction(4.-nMod),nRerolls+1);*/

    double dIntegerPartOfX = std::floor(dX);
    double rollLimit = 4.*dIntegerPartOfX-nMod+3.;
    if(rollLimit<2.)
        return anyCritFailProbability;

    double individualNotTooLarge = rollResult->distributionFunction(rollLimit)-rollResult->distributionFunction(1.);

    
    double probability = 1.;
    for (unsigned int i=0; i<=nRerolls; ++i) {
       probability = individualCritFailProbability + individualNotTooLarge*probability + (1.-individualNotTooLarge - individualCritFailProbability)*(1.-std::pow(1.-rollResult->distributionFunction(1.),i));
    }

    return probability;
}
