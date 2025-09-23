import numpy as np
import math
import argparse
import subprocess
import shutil
import os

def main(file,size):

    data = np.loadtxt(file)
    Ccoefficents             = np.zeros((size,size))
    Scoefficents             = np.zeros((size,size))
    normalizing_constants = np.ones((size+1,size+1))
    Ccoefficents_norm        = np.zeros((size,size))
    Scoefficents_norm        = np.zeros((size,size))
    for row in data:
        l = int(row[0])
        m = int(row[1])
        Ccoef = row[2]
        Scoef = row[3]

        if m == 0:
             k = 1
        else:
             k = 2

        alpha = (math.factorial(l + m)) / (math.factorial(l - m) * k * (2*l + 1))
        norm = np.sqrt(alpha)

        if (l+1) > size:
             break

        Ccoefficents[m,l] = Ccoef #/norm
        Scoefficents[m,l] = Scoef #/ norm
        normalizing_constants[m,l] = norm

        Ccoefficents_norm[m,l] = Ccoef /norm
        Scoefficents_norm[m,l] = Scoef / norm

        np.savetxt("normalized_constants.txt", Ccoefficents_norm, fmt="%.20f")


if __name__ == "__main__":

    main(file="data/em96_360.txt",size = 8)
