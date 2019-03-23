
#include "objective.h"

  /////////////////////////////////////////////////////
 ///               Schwefel Function               ///
/////////////////////////////////////////////////////

RealVec& Schwefel::eval(RealVec& solution, Real& w1, Real& w2) {
        Real obj = 0.; Real pnlt = 0.;
        for(auto&& s: solution)
                obj += -s * sin(pow(abs(s),0.5));
        static RealVec ans(2);
        ans[0] = obj; ans[1] = pnlt;
        penalize(ans, w1, w2);
        return ans;
}

void Schwefel::penalize(RealVec& answer, Real& w1, Real& w2) {answer[0] *= pow(w1*(1 + answer[1]), w2);}

  /////////////////////////////////////////////////////
 ///               Sphere Function                 ///
/////////////////////////////////////////////////////

RealVec& Sphere::eval(RealVec& solution, Real& w1, Real& w2) {
        Real obj = 0.; Real pnlt = 0.;
        for(auto&& s: solution)
                obj += pow(s,2.);
        static RealVec ans(2);
        ans[0] = obj; ans[1] = pnlt;
        penalize(ans, w1, w2);
        return ans;
}

void Sphere::penalize(RealVec& answer, Real& w1, Real& w2) {answer[0] *= pow(w1*(1 + answer[1]), w2);}