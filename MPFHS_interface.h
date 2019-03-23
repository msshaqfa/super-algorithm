//
// Created by shaqfa on 13/02/19.
//

#ifndef MODIFIEDPSFHS_MPFHS_INTERFACE_H
#define MODIFIEDPSFHS_MPFHS_INTERFACE_H

#include "types.h"
#include "MPSFHS.h"
#include "population.h"
#include "MPSFHS.h"
#include "write_CSV.h"

class optimization{

private:
    bool SaveResults, PlotFigures;
    Real HMCRi, PARi, HMCR_max, PAR_min, m, w1, w2;
    UInt dim, popSize, MaxItr;
    RealVec LB, UB, Steps;
    std::shared_ptr<objective> ob;
    RealMat temp1; // delete

public:
    RealMat HarmonyMemory, HMCRH, PARH;
    RealVec FunVal, Penalties, BestHistory;
    UIntMat OTM;

public:
    optimization(UInt& dim, UInt& popSize, UInt& MaxItr,
            Real& HMCRi, Real& PARi, Real& HMCR_max,
            Real& PAR_min, Real& m, Real& w1, Real& w2,
            std::shared_ptr<objective>& ob, RealVec& LB, RealVec& UB, RealVec& Steps, bool&, bool&);

    void optimize();

};

#endif //MODIFIEDPSFHS_MPFHS_INTERFACE_H
