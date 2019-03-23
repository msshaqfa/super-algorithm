  /////////////////////////////////////////////////////
 ///               Mahmoud S. Shaqfa               ///
/////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <memory>
#include "types.h"
#include "population.h"
#include "randomness_generator.h"
#include <ctime>
#include <cstdlib>
#include "objective.h"
#include "vectorized_operations.h"
#include "MPSFHS.h"
#include <algorithm>
#include <time.h>
#include "MPFHS_interface.h"
#include "write_CSV.h"

int main() {

    std::clock_t t1;
    t1 = clock();

    // Define Inputs:
    bool SaveResults = false; // "true" or "false" to export CSV files
    bool PlotFigures = true; // needs python3 and SavingResults activated!

    UInt Dimensions = 100;    // Dimensions of the problem
    UInt HMS = 25;            // Harmony Memory Size (Population Samples)
    UInt MaxItr = 300000;     // Max. Iterations

    Real HMCRi = 0.75;        // Initial HMCR
    Real PARi = 0.15;         // Initial PAR
    Real HMCR_max = 0.99;     // Max HMCR
    Real PAR_min = 0.05;      // Min PAR
    Real m = 2.5;             // Rehearsal Multiplier

    UInt obj = 1;             // [1]-> Schwefel; [2]-> Sphere
    Real w1 = 1.;             // Penalty Multiplier
    Real w2 = 2.;             // Penalty Exponent
    Real Step = 0.01;         // Step accuracy of the solutions
    Real LBV, UBV;


    // Do not Edit!
    std::shared_ptr<objective> ob = nullptr;
    if ((obj ==1u) == true){
        LBV = -500, UBV = 500;
        ob = std::make_shared<Schwefel>();
    } else if((obj == 2u) == true){
        LBV = -5.12, UBV = 5.12;
        ob = std::make_shared<Sphere>();
    }
    RealVec LB(Dimensions, LBV), UB(Dimensions, UBV), Steps(Dimensions, Step);


    // Start optimizing (Do Not Edit!):

    std::unique_ptr<optimization> opt_init(new optimization(Dimensions, HMS, MaxItr, HMCRi, PARi,
            HMCR_max, PAR_min, m, w1, w2, ob, LB, UB, Steps, SaveResults, PlotFigures));
    opt_init->optimize();

    std::cout << "\n\nTotal elapsed time: "<< (Real)(clock() - t1)/CLOCKS_PER_SEC<< " Sec.\n\n"<< std::endl;

}
