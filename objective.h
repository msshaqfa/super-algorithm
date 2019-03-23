  /////////////////////////////////////////////////////
 ///               Mahmoud S. Shaqfa               ///
/////////////////////////////////////////////////////

#ifndef MODIFIEDPSFHS_OBJECTIVE_H
#define MODIFIEDPSFHS_OBJECTIVE_H

#include "types.h"
#include <math.h>

// Abstract class - Objective Interface
class objective{

public:
    virtual RealVec& eval(RealVec&, Real&, Real&){};

private:
    virtual void penalize(RealVec&, Real&, Real&){};
};

// Schwefel Function
class Schwefel : public objective{

public:
    RealVec& eval(RealVec&, Real&, Real&) override;

private:
    void penalize(RealVec&, Real&, Real&) override;
};

//Sphere Function
class Sphere : public objective{

public:
    RealVec& eval(RealVec&, Real&, Real&) override;

private:;
    void penalize(RealVec&, Real&, Real&) override;
};

#endif //MODIFIEDPSFHS_OBJECTIVE_H
