//
// Created by mahmoud on 10/02/19.
//

#ifndef MODIFIEDPSFHS_RANDOMENGINE_H
#define MODIFIEDPSFHS_RANDOMENGINE_H

#include "types.h"
#include <time.h>
#include <random>
#include <chrono>
#include <cstdlib>
#include <ctime>

class random{
public:

    random(){}
    ~random(){}

    static Real& generate(const Real& a = 0., const Real& b = 1.){
        // The new style (C++11) and above - need to be fixed! not working.
        static Real random_result;
        std::mt19937 generator;
        //generator.seed(std::time(0));
        std::uniform_real_distribution<> dis(a, b);  // uniformly distributed
        random_result = dis(generator);
        return random_result;
    }

    static Real& conventional(const Real& a = 0., const Real& b = 1.){
        // Old style - must be seeded once at the main -> Population class
        static Real random_result = 0.;
        random_result = a + (b-a) * ((double)std::rand()/(double)RAND_MAX);
        return random_result;
    }

    static UInt & UIntConventional(const UInt& a = 0, const UInt& b = 1){
        static UInt random_result = 0;
        random_result = a + (std::rand() % static_cast<int>(b - a + 1));
        return random_result;
    }

};

#endif //MODIFIEDPSFHS_RANDOMENGINE_H
