import numpy as np
import matplotlib.pyplot as plt
# import math

'''
Assignment: https://cw.fel.cvut.cz/wiki/courses/b0b33opt/cviceni/hw/lsq1/start

'''

# data_wages = np.loadtxt("mzdy.txt", dtype=float)
# years = []
# wages = []
# for i in range(0, (int(data_wages.size/2))):
#     years.append(data_wages[i][0])
#     wages.append(data_wages[i][1])

# print(years)
# print(wages)

# data_temp = np.loadtxt("teplota.txt", dtype=float)
# days = []
# temperatures = []
# for i in range(0, (int(data_temp.size/2))):
#     days.append(int(data_temp[i][0]))
#     temperatures.append(data_temp[i][1])

# print(days)
# print(temperatures)


def fit_wages(t, M):
    '''
    t a M jsou vektory délky m s časy a mzdami
    x je vektor délky 2 s parametry (x1,x2)
    '''
    A = np.vstack([np.ones(len(t)), t]).T
    x1, x2 = np.linalg.lstsq(A, M, rcond=None)[0]
    # _=plt.plot(t, M, 'o', label='Original data', markersize=5)
    # _=plt.plot(t, x1 + x2*np.array(t), 'r', label='Fitted line')
    # _=plt.legend()
    # plt.show()
    # plt.savefig("wages.png")
    return (x1, x2)


def quarter2_2009(x):
    '''
    pro parametry x odhadnuté funkcí fit_wages spočítá odhad PHM ve druhém kvartálu roku 2009
    '''
    return x[0] + x[1]*2009.25


def fit_temps(t, T, omega):
    '''
    t a T jsou vektory délky m s časy a teplotami, omega je skalár, a x je vektor délky 4 s parametry (x1,x2,x3,x4)
    '''
    A = np.vstack([np.ones(len(t)), t, np.sin(
        omega*np.array(t)), np.cos(omega*np.array(t))]).T
    x1, x2, x3, x4 = np.linalg.lstsq(A, T, rcond=None)[0]
    # _=plt.plot(t, T, 'o', label='Original data', markersize=5)
    # _=plt.plot(t, x1 + x2*np.array(t)+x3*np.sin(omega*np.array(t)) + x4*np.cos(omega*np.array(t)), 'r', label='Fitted line')
    # _=plt.legend()
    # plt.show()
    # plt.savefig("temps.png")
    return (x1, x2, x3, x4)

# x1_w, x2_w = fit_wages(years, wages)
# print(x1_w, x2_w)
# q = quarter2_2009((x1_w, x2_w))
# print(q)

# x1_t, x2_t, x3_t, x4_t = fit_temps(days, temperatures, (2*math.pi)/365)
# print(x1_t, x2_t, x3_t, x4_t)
