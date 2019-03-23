import csv
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec

class Reader:
    def __init__(self, file_name):
        self.file_name = file_name + ".csv";
        self.reader = csv.reader(open(self.file_name, "r"), delimiter=",")
    
    def Read(self):
        temp = list(self.reader);
        variable = np.array(temp).astype("float")
        return variable
    
    def __del__(self):
        pass

if __name__ == "__main__":
    
    # Read CSV files into Python's memory as variables
    r1 = Reader("HarmonyMemory")
    HM = r1.Read()
    r2 = Reader("OTM")
    OTM = r2.Read()
    r3 = Reader("HMCRH")
    HMCRH = r3.Read()
    r4 = Reader("PARH")
    PARH = r4.Read()
    r5 = Reader("BestHistory")
    BestHistory = r5.Read()
    del r1, r2, r3, r4, r5
    
    MaxItr = len(BestHistory)
    N = HM.shape[1]
    X_array =np.float64(range(MaxItr))

    # plot
    fig = plt.figure()
    gs = gridspec.GridSpec(2, 2)
    plt.subplot(gs[0, :])
    plt.semilogx(X_array, BestHistory)
    plt.title("Objective Function")
    plt.xlabel("Iterations")
    plt.ylabel("Fitness")
    plt.grid(True)
    
    plt.subplot(gs[1, 0])
    for k in range(N):
        plt.semilogx(X_array, HMCRH[0:MaxItr,k])
    plt.title("HMCR History")
    plt.xlabel("Iterations")
    plt.ylabel("HMCR Probabilities")
    plt.grid(True)
    
    plt.subplot(gs[1, 1])
    for k in range(N):
        plt.semilogx(X_array, PARH[0:MaxItr,k])
    plt.title("PAR History")
    plt.xlabel("Iterations")
    plt.ylabel("PAR Probabilities")
    plt.grid(True)
    
    plt.show()
    
