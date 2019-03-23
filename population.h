  /////////////////////////////////////////////////////
 ///               Mahmoud S. Shaqfa               ///
/////////////////////////////////////////////////////

#ifndef MODIFIEDPSFHS_POPULATION_H
#define MODIFIEDPSFHS_POPULATION_H
#include "types.h"
#include <iostream>
#include "vectorized_operations.h"
#include "objective.h"
#include "randomness_generator.h"
#include <cmath>

using namespace vo;

class Population {

public:
    UInt dim, popSize;
    RealVec LB, UB, Steps;
    Real w1, w2;

public:
    Population(RealMat&, UInt&, UInt&, RealVec&,
            RealVec&, RealVec&, Real&, Real&);

    void eval(RealMat&, std::shared_ptr<objective>&, RealVec&, RealVec&);

private:
    void Initialize(RealMat&);

};

#endif //MODIFIEDPSFHS_POPULATION_H
