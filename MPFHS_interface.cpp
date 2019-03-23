
#include "MPFHS_interface.h"

optimization::optimization(UInt &dim, UInt &popSize, UInt &MaxItr, Real &HMCRi, Real &PARi, Real &HMCR_max,
                           Real &PAR_min, Real &m, Real &w1, Real &w2, std::shared_ptr<objective>& ob, RealVec &LB,
                           RealVec &UB, RealVec &Steps, bool& SaveResults, bool& PlotFigures): dim(dim), popSize(popSize), MaxItr(MaxItr), HMCRi(HMCRi),
                           PARi(PARi), HMCR_max(HMCR_max), PAR_min(PAR_min), m(m), w1(w1), w2(w2), ob(ob), LB(LB),
                           UB(UB), Steps(Steps), SaveResults(SaveResults), PlotFigures(PlotFigures){

    // Allocating containers:

    FunVal.resize(popSize);
    Penalties.resize(popSize);

    HarmonyMemory.resize(popSize);
    OTM.resize(popSize);

    HMCRH.resize(MaxItr);
    PARH.resize(MaxItr);
    BestHistory.resize(MaxItr);

    std::fill(FunVal.begin(), FunVal.end(), 0.);
    std::fill(Penalties.begin(), Penalties.end(), 0.);

    std::fill(HarmonyMemory.begin(), HarmonyMemory.end(), RealVec(dim, 0.));
    std::fill(OTM.begin(), OTM.end(), UIntVec(dim, 0));

    std::fill(HMCRH.begin(), HMCRH.end(), RealVec(dim, 0.));
    std::fill(PARH.begin(), PARH.end(), RealVec(dim, 0.));
    std::fill(BestHistory.begin(), BestHistory.end(), 0.);

}

void optimization::optimize() {

    // Populate
    std::unique_ptr<Population>pop_(new Population(HarmonyMemory, dim, popSize, LB, UB, Steps, w1, w2));
    pop_->eval(HarmonyMemory, ob, FunVal, Penalties);
    temp1 = HarmonyMemory;
    // Optimize
    std::unique_ptr<MPSFHS>MPSFHS_(new MPSFHS(HMCRi, PARi, HMCR_max, PAR_min, MaxItr, m, dim, popSize, w1,
            w2, LB, UB, Steps));
    MPSFHS_->Initiate(ob, HarmonyMemory, HMCRH, PARH, OTM, BestHistory, FunVal, Penalties);

    // Flush
    if (SaveResults) {
        std::cout<< "\n\nPlease wait! writing *.CSV files depends on your HDD/SSD writing speed ...\n\n"<<std::endl;
        Str OTM_name = "OTM", HMCRH_name = "HMCRH", PARH_name = "PARH", HM_name = "HarmonyMemory", BH_name = "BestHistory";
        std::unique_ptr<csv_dump> OTM_flush1(new csv_dump(OTM_name));
        OTM_flush1->dump(OTM);
        std::unique_ptr<csv_dump> OTM_flush2(new csv_dump(HMCRH_name));
        OTM_flush2->dump(HMCRH);
        std::unique_ptr<csv_dump> OTM_flush3(new csv_dump(PARH_name));
        OTM_flush3->dump(PARH);
        std::unique_ptr<csv_dump> OTM_flush4(new csv_dump(HM_name));
        OTM_flush4->dump(HarmonyMemory);
        std::unique_ptr<csv_dump> OTM_flush5(new csv_dump(BH_name));
        OTM_flush5->dump(BestHistory);
    }

    // plotting
    if (SaveResults && PlotFigures)
        std::system("python3 plotter.py");

}