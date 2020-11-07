"""
    Vladescu Cristiana, 342 C4
    Laboratorul 2
"""
import matplotlib.pyplot as plt
from math import log
nprocs = [2, 4, 8, 16, 32, 64]

#Parallel and Sequential Bubble Sort
#Articol: https://issuu.com/williamss98675d/docs/11319ijcsit05

def main():
    O_1 = []
    T_1 = []
    O_n = []
    T_n = []
    S_n = []
    E_n = []
    R_n = []
    U_n = []
    Q_n = []

    for n in nprocs:
        O_1_curr = pow(n, 2)
        O_1.append(O_1_curr)

        T_1_curr = pow(n, 2)
        T_1.append(T_1_curr)

        O_n_curr = n * log(n,2)
        O_n.append(O_n_curr)

        T_n_curr = pow(n,2) / 2 * n
        T_n.append(T_n_curr)

        S_n_curr = T_1_curr / T_n_curr
        S_n.append(S_n_curr)

        E_n_curr = S_n_curr / n
        E_n.append(E_n_curr)

        R_n_curr = O_n_curr / O_1_curr
        R_n.append(R_n_curr)

        U_n_curr = R_n_curr * E_n_curr
        U_n.append(U_n_curr)

        Q_n_curr = S_n_curr * E_n_curr / R_n_curr
        Q_n.append(Q_n_curr)

    plt.plot(nprocs, E_n, label = 'E_n')
    plt.plot(nprocs, U_n, label = 'U_n')
    plt.plot(nprocs, S_n, label = 'S_n')
    plt.plot(nprocs, R_n, label = 'R_n')
    plt.plot(nprocs, Q_n, label = 'Q_n')
    plt.legend()
    plt.show()
    plt.savefig("parallel_bubble_sort.png")

        
if __name__ == "__main__":

    main()
