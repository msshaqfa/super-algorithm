
#include "MPSFHS.h"

MPSFHS::MPSFHS(Real& HMCRi, Real& PARi, Real& HMCR_max, Real& PAR_min,
        UInt& MaxItr, Real& m, UInt& dim, UInt& PopSize, Real& w1, Real& w2,
        RealVec& LB, RealVec& UB, RealVec& Steps): HMCRi(HMCRi),PARi(PARi),
        PAR_min(PAR_min), HMCR_max(HMCR_max), MaxItr(MaxItr), m(m), dim(dim),
        popSize(PopSize), w1(w1), w2(w2), LB(LB), UB(UB), Steps(Steps){}

void MPSFHS::Initiate(std::shared_ptr<objective>& obj, RealMat& BasicPopulation,
        RealMat& HMCRH, RealMat& PARH, UIntMat& OTM, RealVec& BestHistory,
        RealVec& FunVal, RealVec& Penalties){

    // Local variables
    UInt HMCR_id = 1, PAR_id = 2, Random_id = 3;
    UInt Rehearsals = (UInt)ceil(m * popSize);
    RealVec Xnew(dim,0);
    UIntVec OI(dim,0);
    RealVec Fnew(2);
    UInt worstIdx;
    Real HMCR, PAR;

std::cout<<"\n  /////////////////////////////////////////////////////"<<std::endl;
std::cout<<" ///               The Rehearsal Step              ///"<<std::endl;
std::cout<<"/////////////////////////////////////////////////////\n"<<std::endl;

// fill up HMCRH and PARH
std::fill(HMCRH.begin(), HMCRH.begin() + Rehearsals, RealVec(dim, HMCRi));
std::fill(PARH.begin(), PARH.begin() + Rehearsals, RealVec(dim, PARi));

for(UInt i = 0; i < Rehearsals; ++i){
    for(UInt j = 0; j < dim; ++j){
        if (random::conventional() < HMCRi){
            Xnew[j] = BasicPopulation[random::UIntConventional(0, popSize-1)][j];
            OI[j] = HMCR_id;
            if(random::conventional() < PARi){
                Xnew[j] += pow(-1, random::UIntConventional(1,2)) *
                        round(random::conventional()*(UB[j]-LB[j])/Steps[j])*Steps[j];
                OI[j] = PAR_id;
            }
        } else{
            Xnew[j] = LB[j]+round(random::conventional()*(UB[j]-LB[j])/Steps[j])*Steps[j];
            OI[j] = Random_id;
        }
        Xnew[j] = std::min(std::max(Xnew[j], LB[j]), UB[j]);
    }

    Fnew = obj->eval(Xnew, w1, w2);
    worstIdx = vo::maxIdx(FunVal);
    if(Fnew[0] < FunVal[worstIdx]){
        FunVal[worstIdx] = Fnew[0];
        Penalties[worstIdx] = Fnew[1];
        vo::replace_row(BasicPopulation, Xnew, worstIdx);
        vo::replace_row(OTM, OI, worstIdx);
    }
    std::cout<<"Iteration No. "<<i<<", BestFitness = "<<vo::minVal(FunVal)<<
    ", Penalty= "<<Penalties[vo::minIdx(FunVal)]<<std::endl;
    BestHistory[i] = vo::minVal(FunVal);
}

std::cout<< "\n  /////////////////////////////////////////////////////"<<::std::endl;
std::cout<< " ///               The Performance Step            ///"<<::std::endl;
std::cout<< "/////////////////////////////////////////////////////\n"<<::std::endl;

for(UInt i = Rehearsals; i < MaxItr; ++i){
    for(UInt j = 0; j < dim; ++j){
        // Multi-threading ?
        HMCR = (Real)vo::sum_eq_col(OTM, j, HMCR_id) / OTM.size();
        HMCR = std::max(HMCRi, std::min(HMCR_max, HMCR));          // SHAQFA and ORBAN
        PAR = (Real)vo::sum_eq_col(OTM, j, PAR_id) / OTM.size();   // SHAQFA and ORBAN
        PAR = std::max(PAR_min, std::min(PARi, PAR));
        HMCRH[i][j] = HMCR;
        PARH[i][j] = PAR;
        if (random::conventional() < HMCR){
            Xnew[j] = BasicPopulation[random::UIntConventional(0, popSize-1)][j];
            OI[j] = HMCR_id;
            if(random::conventional() < PAR){
                Xnew[j] += pow(-1, random::UIntConventional(1,2)) *
                           round(random::conventional()*(UB[j]-LB[j])/Steps[j])*Steps[j];
                OI[j] = PAR_id;
            }
        } else{
            Xnew[j] = LB[j]+round(random::conventional()*(UB[j]-LB[j])/Steps[j])*Steps[j];
            OI[j] = Random_id;
        }
        Xnew[j] = std::min(std::max(Xnew[j], LB[j]), UB[j]);
    }
    Fnew = obj->eval(Xnew, w1, w2);
    worstIdx = vo::maxIdx(FunVal);
    if(Fnew[0] < FunVal[worstIdx]){
        FunVal[worstIdx] = Fnew[0];
        Penalties[worstIdx] = Fnew[1];
        vo::replace_row(BasicPopulation, Xnew, worstIdx);
        vo::replace_row(OTM, OI, worstIdx);
    }
    std::cout<<"Iteration No. "<<i<<", BestFitness = "<<vo::minVal(FunVal)<<
    ", Penalty= "<<Penalties[vo::minIdx(FunVal)]<<std::endl;
    BestHistory[i] = vo::minVal(FunVal);
}
std::cout << "\n\nBest solution vector: " <<std::endl;
UInt last_min = vo::minIdx(FunVal), spacer = 1;
for (UInt k =1; k < dim+1; ++k){
    std::cout<<" X"<<k<<": "<< BasicPopulation[last_min][k-1]<<" ||"; spacer++;
    if (spacer == 6){
        std::cout<<" ..."<<std::endl; spacer=0;
        std::cout<<"----------------"<<std::endl;
    }
}
std::cout<<std::endl;
std::cout << "\nWith a fitness of: "<<FunVal[last_min]<<std::endl;
}