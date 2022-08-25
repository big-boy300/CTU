import numpy as np
import scipy.optimize as opt

'''
Assignment: https://cw.fel.cvut.cz/wiki/courses/b0b33opt/cviceni/hw/lp1/start
'''


def vyhra(c, k):
    coefs = np.multiply(c, -1)
    n = np.shape(coefs)[0]+1
    c_var = np.zeros(n)
    c_var[n-1] = -1
    A_ub = np.zeros([3, n])
    for i in range(0, 3):
        if i == 0:
            A_ub[i] = [coefs[0], coefs[1], 0, 0, 0, 1]
        elif i == 1:
            A_ub[i] = [0, coefs[1], coefs[2], coefs[3], 0, 1]
        elif i == 2:
            A_ub[i] = [0, 0, 0, coefs[3], coefs[4], 1]

    b_ub = np.zeros(3)
    A_eq = [[1, 1, 1, 1, 1, 0]]
    b_eq = k
    bounds = [(0, None), (0, None), (0, None), (0, None), (0, None), (0, None)]
    res = opt.linprog(c_var, A_ub, b_ub, A_eq, b_eq, bounds)
    fin = opt.OptimizeResult.pop(res, "x")[0:5]

    return fin


def vyhra2(c, k, m):
    coefs = np.multiply(c, -1)
    n = np.shape(coefs)[0]+1
    c_var = np.zeros(n)
    c_var[n-1] = -1
    A_ub = np.zeros([3, n])
    for i in range(0, 3):
        if i == 0:
            A_ub[i] = [coefs[0], 0, 0, 1]
        elif i == 1:
            A_ub[i] = [0, coefs[1], 0, 1]
        elif i == 2:
            A_ub[i] = [0, 0, coefs[2], 1]

    b_ub = np.zeros(3)
    A_eq = [[1, 1, 1, 0]]
    b_eq = k
    bounds = [(m, None), (m, None), (m, None), (0, None)]
    res = opt.linprog(c_var, A_ub, b_ub, A_eq, b_eq, bounds)
    fin = opt.OptimizeResult.pop(res, "x")[0:3]
    return fin


def minimaxfit(x, y):
    n = np.shape(x)[0]
    m = np.shape(x)[1]
    c_var = np.append(np.zeros(n+1), 1)
    A_ub = np.zeros([m*2, n+2])
    for i in range(0, m):
        tmp = x.T[i]
        A_ub[i] = np.append(np.append(tmp, 1), -1)
        A_ub[i+m] = np.append(np.append(np.multiply(tmp, -1), -1), -1)

    b_ub = np.zeros(m * 2)
    for i in range(0, m):
        b_ub[i] = y[0][i]
        b_ub[i+m] = y[0][i] * -1

    res = opt.linprog(c_var, A_ub, b_ub, bounds=(-np.inf, np.inf))
    fin = opt.OptimizeResult.pop(res, "x")

    a = fin[0:n]
    b = fin[n]
    r = fin[n+1]

    return a, b, r


if (__name__ == '__main__'):
    # kurzy c = (c1, c10, c0, c02, c2)
    c = np.array([1.27, 1.02, 4.70, 3.09, 9.00])
    k = 3000  # mnozstvi penez

    x = vyhra(c, k)
    # print(x)

    c = np.array([1.27, 4.70, 9.00])
    k = 3000
    m = 400
    x = vyhra2(c, k, m)
    # print(x)

    x = np.array([[1, 2, 3, 3, 2], [4, 1, 2, 5, 6], [7, 8, 9, -5, 7]])
    y = np.array([[7, 4, 1, 2, 5]])
    a, b, r = minimaxfit(x, y)
    # print(a)
    # print(b)
    # print(r)
