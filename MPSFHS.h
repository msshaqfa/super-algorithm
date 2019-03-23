
  /////////////////////////////////////////////////////
 ///               Mahmoud S. Shaqfa               ///
/////////////////////////////////////////////////////

#ifndef MODIFIEDPSFHS_MPSFHS_H
#define MODIFIEDPSFHS_MPSFHS_H
#include <cmath>
#include <algorithm>
#include "types.h"
#include "vectorized_operations.h"
#include "MPSFHS.h"
#include "randomness_generator.h"
#include "objective.h"
#include <zconf.h> // sleep(sec.)

class MPSFHS{

private:
    Real HMCRi, PARi, m, PAR_min, HMCR_max, w1, w2;
    UInt MaxItr, dim, popSize;
    RealVec LB, UB, Steps;

public:
    MPSFHS(Real&, Real&, Real&, Real&, UInt&, Real&, UInt&, UInt&, Real&, Real&, RealVec&, RealVec&, RealVec&);

    ~MPSFHS(){}

    void Initiate(std::shared_ptr<objective>&, RealMat&,RealMat&, RealMat&, UIntMat&, RealVec&, RealVec&, RealVec&);

};
#endif //MODIFIEDPSFHS_MPSFHS_H
