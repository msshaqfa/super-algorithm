
#include "population.h"

Population::Population(RealMat& BasicPopulation, UInt& dim, UInt& PopSize, RealVec&LB,
        RealVec& UB, RealVec& Steps, Real& w1, Real& w2)
        : dim(dim) , popSize(PopSize), LB(LB), UB(UB), Steps(Steps), w1(w1), w2(w2) {
    std::srand(std::time(0));
    Initialize(BasicPopulation);
}

void Population::Initialize(RealMat& BasicPopulation){
    for(UInt i=0; i<popSize;++i){
        for(UInt j=0; j<dim;++j){
            BasicPopulation[i][j] = LB[j] +
                    round(random::conventional()*(UB[j]-LB[j])/Steps[j])*Steps[j];
        }
    }
}

void Population::eval(RealMat& BasicPopulation, std::shared_ptr<objective>& obj, RealVec& FunVal, RealVec& Penalties) {
    RealVec ans(2); UInt id = 0;
    for(auto&& v: BasicPopulation){
        ans = obj->eval(v, w1, w2);
        FunVal[id] = ans[0]; Penalties[id] = ans[1]; id++;
    }
}