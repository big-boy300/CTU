import math
import scipy.io as sio
import numpy as np
from math import pi
from matplotlib import pyplot as plt
import random

'''
Assignment: https://cw.fel.cvut.cz/wiki/courses/b0b33opt/cviceni/hw/kruznice_lin/start
'''


def quad_to_center(d, e, f):
    x0 = -d/2
    y0 = -e/2
    r = math.sqrt((d**2)/4 + (e**2)/4 - f)

    return x0, y0, r


def fit_circle_nhom(X):
    n = X.shape[0]
    x_vals = np.empty(n)
    y_vals = np.empty(n)
    vec = np.empty(n)
    for i in range(0, n):
        x_vals[i] = X.T[0][i]
        y_vals[i] = X.T[1][i]
        vec[i] = -1 * (X.T[0][i] ** 2 + X.T[1][i] ** 2)

    mat = np.vstack([x_vals, y_vals, np.ones(X.shape[0])]).T
    d, e, f = np.linalg.lstsq(mat, vec.T, rcond=None)[0]
    return d, e, f


def fit_circle_hom(X):
    n = X.shape[0]
    a_vals = np.empty(n)
    x_vals = np.empty(n)
    y_vals = np.empty(n)
    for i in range(0, n):
        a_vals[i] = X.T[0][i] ** 2 + X.T[1][i] ** 2
        x_vals[i] = X.T[0][i]
        y_vals[i] = X.T[1][i]

    mat = np.vstack([a_vals, x_vals, y_vals, np.ones(X.shape[0])]).T

    eigVals, eigVects = np.linalg.eig(mat.T @ mat)
    eigValsSorted = np.sort(eigVals)
    eigValsList = eigVals.tolist()

    eigVectorsSorted = np.empty(np.shape(eigVects))
    for i in range(0, len(eigValsSorted)):
        idx = eigValsList.index(eigValsSorted[i])
        eigVectorsSorted[i] = eigVects.T[idx]

    eigVectMin = eigVectorsSorted[0]

    a = eigVectMin.T[0]
    d = eigVectMin.T[1] / a
    e = eigVectMin.T[2] / a
    f = eigVectMin.T[3] / a

    return d, e, f


def dist(X, x0, y0, r):
    N = X.shape[0]
    ret = np.empty(N)
    for i in range(0, N):
        ret[i] = math.sqrt((X[i][0]-x0)**2 + (X[i][1]-y0)**2) - r

    return ret


def fit_circle_ransac(X, num_iter, threshold):
    n = np.shape(X)[0]
    X_list = X.tolist()
    inlinersNum = np.zeros(num_iter)
    allCircles = np.zeros([n, 3], dtype=np.complex64)
    for i in range(0, num_iter):
        arr = np.array(random.sample(X_list, k=3))
        d, e, f = fit_circle_hom(arr)
        x0, y0, r = quad_to_center(d, e, f)
        allCircles[i][0] = x0
        allCircles[i][1] = y0
        allCircles[i][2] = r
        var = dist(X, x0, y0, r)
        for k in range(0, len(var)):
            if abs(var[k]) < threshold:
                inlinersNum[i] += 1

    maxElem = np.amax(inlinersNum)
    inlinersNum_list = inlinersNum.tolist()
    idx = inlinersNum_list.index(maxElem)
    x0 = allCircles[idx][0]
    y0 = allCircles[idx][1]
    r = allCircles[idx][2]
    return x0, y0, r


def plot_circle(x0, y0, r, color, label):
    t = np.arange(0, 2*pi, 0.01)
    X = x0 + r*np.cos(t)
    Y = y0 + r*np.sin(t)
    plt.plot(X, Y, color=color, label=label)


if (__name__ == '__main__'):
    data = sio.loadmat('data.mat')
    X = data['X']  # only inliers
    A = data['A']  # X + outliers

    def_nh = fit_circle_nhom(X)
    x0y0r_nh = quad_to_center(*def_nh)
    dnh = dist(X, *x0y0r_nh)

    def_h = fit_circle_hom(X)
    x0y0r_h = quad_to_center(*def_h)
    dh = dist(X, *x0y0r_h)

    results = {'def_nh': def_nh, 'def_h': def_h,
               'x0y0r_nh': x0y0r_nh, 'x0y0r_h': x0y0r_nh,
               'dnh': dnh, 'dh': dh}

    GT = sio.loadmat('GT.mat')
    for key in results:
        print('max difference',  np.amax(
            np.abs(results[key] - GT[key])), 'in', key)

    x = fit_circle_ransac(A, 2000, 0.1)

    plt.figure(1)
    plt.subplot(121)
    plt.scatter(X[:, 0], X[:, 1], marker='.', s=3)
    plot_circle(*x0y0r_h, 'r', 'hom')
    plot_circle(*x0y0r_nh, 'b', 'nhom')
    plt.legend()
    plt.axis('equal')
    plt.subplot(122)
    plt.scatter(A[:, 0], A[:, 1], marker='.', s=2)
    plot_circle(*x, 'y', 'ransac')
    plt.legend()
    plt.axis('equal')
    plt.show()
    plt.savefig('hw4.png')
