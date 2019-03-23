'''
%*************************************************************************%
% All rights reserved © to the authors: Mahmoud SHAQFA and Zoltan ORBAN   %
%                                                                         %
% M. Shaqfa Contact:                                                      %
% Earthquake Engineering and Structural Dynamics Laboratory (EESD),       %
% School of Architecture, Civil and Environmental Engineering (ENAC),     %
% Ecole polytechnique federale de Lausanne (EPFL),                        %
% CH-1015 Lausanne, Switzerland.                                          %
%               Tel.: +41 21 69 33297                                     %
%               Email: mahmoud.shaqfa@epfl.ch                             %
%                                                                         %
% Z. ORBAN Contact:                                                       %
% Department of Structural Engineering,                                   %
% Faculty of Engineering and Information Technology,                      %
% University of Pecs, Boszorkany u. 2,                                    %
% H-7624 Pecs, Hungary.                                                   %
%               Email: orbanz@mik.pte.hu                                  %
%*************************************************************************%
% - This code is just a simple demonstration for the modified algorithm   %
%   without taking into account filtering the population(HM).             %
% - This code is not optimized. A vectorized code should make it          %
%   work faster.                                                          %
%*************************************************************************%
% Main references for this paper and code:                                %
%                                                                         %
% [1] - Geem, Z.W.: Optimal cost design of water distribution             %
%       networks usingharmony search 38, 259-277(2006)                    %
%                                                                         %
% [2] - Geem, Z.W.: Novel derivative of harmony search algorithm for      %
%       discrete design variables. Applied Mathematics and Computation    %
%       199(1), 223-230(2008). DOI https://doi.org/10.1016/j.amc.2007.    %
%       09.049.                                                           %
%                                                                         %
% [3] - Geem, Z.W., Sim, K.B.: Parameter-setting-free harmony search      %
%       algorithm 217, 3881-3889 (2010)                                   %
%*************************************************************************%
% This file is free: you can redistribute it and/or modify                %
% it under the terms of the GNU General Public License as published by    %
% the Free Software Foundation, either version 3 of the License, or       %
% (at your option) any later version.                                     %
%                                                                         %
% This file is distributed in the hope that it will be useful,            %
% but WITHOUT ANY WARRANTY; without even the implied warranty of          %
% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           %
% GNU General Public License for more details.                            %
% TO recieve a copy of GNU License refer to: https://www.gnu.org/licenses/%
%*************************************************************************%
'''

import pyDOE
import math
import matplotlib.pyplot as plt
import random as rand
from abc import ABC
import numpy as np
import time
import copy

class Objective(ABC):
    def __init__(self):
        pass

    @staticmethod
    def compute(SolutionVector):
        raise Exception("pure virtual function")

    def __del__(self):
        pass

class Sphere(Objective):
    def __init__(self):
        pass

    @staticmethod
    def compute(SolutionVector):
        obj = sum(np.power(SolutionVector,2))
        return obj

class Schwefel(Objective):
    def __init__(self):
        pass

    @staticmethod
    def compute(SolutionVector):
        obj = sum(np.multiply(SolutionVector,np.sin(np.sqrt(np.abs(SolutionVector)))))
        return obj

    def __del__(self):
        pass

class Population: # Abstract Class Only
    def __init__(self, Pop_N, LB, UB, Step):
        self.Pop_N=Pop_N; self.LB=LB; self.UB=UB; self.Step=Step;
        self.population = np.zeros([self.Pop_N, len(LB)])

    def Initiate(self):
        raise NotImplementedError

    def __del__(self):
        pass

class LatinHypercubeSampling(Population):
    def __init__(self, Pop_N, LB, UB, Step):
        super().__init__(Pop_N, LB, UB, Step)

    def Initiate(self):
        random_population = pyDOE.lhs(n = len(self.LB)
        , criterion='center', samples = self.Pop_N)
        for i in range(self.Pop_N):
            for j in range(len(self.LB)):
                self.population[i,j] = self.LB[j] + round(random_population[i,j] *
                (self.UB[j] - self.LB[j]) / self.Step[j]) * self.Step[j]
        return self.population

    def __del__(self):
        pass

class MontoCarloSampling(Population):
    def __init__(self, Pop_N, LB, UB, Step):
        super().__init__(Pop_N, LB, UB, Step)

    def Initiate(self):
        for i in range(self.Pop_N):
            for j in range(len(self.LB)):
                self.population[i,j] = self.LB[j] + round(rand.random() *
                (self.UB[j] - self.LB[j]) / self.Step[j]) * self.Step[j]
        return self.population

    def __del__(self):
        pass

class HarmonySearch:
    def __init__(self, Objective, HMS, HMCR, PAR, MaxItr, LB, UB, Step,
                 LHS = 1, PSFHS = 0, m = 2.5, HMCR_max = 0.99, PAR_min = 0.05):
        self.Objective = Objective;
        self.HMS = HMS; self.HMCR = PAR; self.PAR = PAR;
        self.MaxItr = MaxItr;self.LB = LB;self.UB = UB;
        self.Step = Step;self.m=m;self.HMCR_max=HMCR_max;
        self.PAR_min=PAR_min; self.PSFHS = PSFHS;
        self.FunVal = np.zeros(self.HMS);self.Penality = copy.copy(self.FunVal)
        self.Xnew = np.zeros(len(self.LB));self.BestHistory = np.zeros(MaxItr)        
        # LatinHypercubeSampling/ MontoCarloSampling Based HS Algorithm
        if LHS == 1:
            Sample = LatinHypercubeSampling(LB = self.LB,
            UB = self.UB, Step = self.Step, Pop_N = self.HMS,)
        else:
            Sample = MontoCarloSampling(LB = self.LB,
            UB = self.UB, Step = self.Step, Pop_N = self.HMS,)
        self.HM = Sample.Initiate();
        if self.PSFHS == 1:
            self.HMCR_History =  np.zeros([MaxItr, len(self.LB)]);self.Iterator_idx=0
            self.PAR_History = np.zeros([MaxItr, len(self.LB)]);
            self.OI = np.zeros(len(self.LB)); self.OM = np.zeros([self.HMS, len(self.LB)])
            self.HMCR_History[0:math.ceil(self.m * self.HMS)-1][:] = copy.copy(self.HMCR)
            self.PAR_History[0:math.ceil(self.m * self.HMS)-1][:] = copy.copy(self.PAR)

    def HarmonyIterator(self, HM, FunVal, HMCR, PAR):
        # just an internal method - do not call out of this class
        for i in range(len(self.LB)):
            if self.PSFHS == 1:
                if self.Iterator_idx > math.ceil(self.m * self.HMS):
                    HMCR = np.sum(self.OM[:,i] == 1) / self.HMS
                    PAR = np.sum(self.OM[:,i] == 2) / self.HMS
                    HMCR = np.amax([self.HMCR, np.amin([self.HMCR_max, HMCR])]); # SHAQFA and ORBAN
                    PAR  = np.amax([self.PAR_min, np.amin([self.PAR, PAR])]);    # SHAQFA and ORBAN
                self.HMCR_History[self.Iterator_idx, i] = HMCR
                self.PAR_History[self.Iterator_idx, i] = PAR
            if rand.random() < HMCR:
                self.Xnew[i] = HM[rand.randint(0,self.HMS-1)][i]
                if self.PSFHS == 1:self.OI[i] = 1
                if rand.random() < PAR:
                    self.Xnew[i] += (-1.0)**rand.randint(1,2) * float(
                    round((self.UB[i] - self.LB[i]) * 
                          rand.random() / self.Step[i])) * self.Step[i]
                    if self.PSFHS == 1:self.OI[i] = 2
            else:
                self.Xnew[i] = self.LB[i] + float(round((self.UB[i]-
                self.LB[i]) * rand.random() / self.Step[i])) * self.Step[i]
                if self.PSFHS == 1:self.OI[i] = 3
            self.Xnew[i] = max([self.LB[i], min([self.Xnew[i], self.UB[i]])])
        FunNew = self.Objective.compute(self.Xnew)
        Fworst = np.amax(FunVal)
        if FunNew < Fworst:
            Worst_ind = np.argmax(FunVal)
            FunVal[Worst_ind] = FunNew
            HM[Worst_ind][:] = self.Xnew
            if self.PSFHS ==1:self.OM[Worst_ind][:] = self.OI
        ind_best = np.argmin(FunVal)
        BestHistory = FunVal[ind_best]
        return HM, FunVal, BestHistory

    def Optimize(self):
        for i in range(self.HMS):
            self.FunVal[i] = self.Objective.compute(self.HM[:][i])
        j=0; self.Iterator_idx = j
        while (j < self.MaxItr):
            self.HM, self.FunVal, self.BestHistory[j] = self.HarmonyIterator(
                    self.HM, self.FunVal, self.HMCR, self.PAR)
            print("Iteration No. ", str(j), ", The best obtained value = ",
                  str(self.BestHistory[j]))
            j+=1; self.Iterator_idx = j
        if self.PSFHS == 0:
            return (self.HM, self.FunVal, self.BestHistory, 
                    self.HM[np.argmin(self.FunVal)][:])
        else:
            return (self.HM, self.FunVal, self.BestHistory, 
                    self.HM[np.argmin(self.FunVal)][:],
                    self.HMCR_History, self.PAR_History)

    def __del__(self):
        pass

if __name__ == "__main__":
    t1 = time.time() # Tic

    HMS = 25         # Harmony Memory Size (Population samples)
    HMCR = 0.75      # HMCR for Harmony Search and HMCRi for PSFHS
    HMCR_max = 0.99
    PAR = 0.45       # PAR for Harmony Search and PARi for PSFHS
    PAR_min = 0.05
    MaxItr = 300000  # Number of Iterations
    N = 100          # Dimentions of the Problem
    Step = 0.01      # Solution precision
    m = 2.5

    # Select [1]-> to solve Schwefel function and [2]-> the Sphere function
    ObjectiveOpts = 1

    # For PSFHS -> [1], for HarmonySerach -> [0]
    PSFHS = 1

    if   ObjectiveOpts == 1:
        LBV = -500; UBV = 500
        ob = Schwefel();
    elif ObjectiveOpts == 2:
        LBV = -5.12; UBV = 5.12
        ob = Sphere();

    UB = np.ones(N) * UBV
    LB = np.ones(N) * LBV
    Steps = np.ones(N) * Step;

    HS_TEST = HarmonySearch(ob, HMS, HMCR, PAR, MaxItr, LB, UB, Steps, LHS = 1,
                            PSFHS = PSFHS, m = m, HMCR_max = HMCR_max,
                            PAR_min = PAR_min)
    if PSFHS == 1:
        HM, FunVal, BestHistory, BestVector, HMCRH, PARH = HS_TEST.Optimize()
    else:
         HM, FunVal, BestHistory, BestVector = HS_TEST.Optimize()
         HMCRH =  np.zeros([MaxItr, N]); PARH = np.zeros([MaxItr, N]);
         HMCRH[:][:] = HMCR; PARH[:][:] = PAR;

    print("\n","The elapsed time is: ", str(time.time()-t1), " sec\n")
    plt.semilogx(range(MaxItr), BestHistory)
    print("\n Best Vector Obtained: ", BestVector)
    print("\n Evaluation of best vector: ", ob.compute(BestVector))
    plt.title("Objective Function")
    plt.xlabel("Iterations")
    plt.ylabel("Fitness")
    plt.grid(True)
    plt.show()

    plt.figure()
    for k in range(len(LB)):
        plt.semilogx(range(MaxItr), HMCRH[:,k])
    plt.title("HMCR History")
    plt.xlabel("Iterations")
    plt.ylabel("HMCR Probabilities")
    plt.grid(True)
    plt.show()

    plt.figure()
    for k in range(len(LB)):
        plt.semilogx(range(MaxItr), PARH[:,k])
    plt.title("PAR History")
    plt.xlabel("Iterations")
    plt.ylabel("PAR Probabilities")
    plt.grid(True)
    plt.show()