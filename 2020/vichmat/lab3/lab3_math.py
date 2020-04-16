import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
import numpy as np
import copy

class Lab3:

    def __init__(self):
        self.V = 200000.
        self.S = 3400.
        self.l = 170.
        self.H = -170.
        self.p1 = 75.
        self.v = 12.5

    def dydt(self, y, z, t):
        return z

    def dzdt(self, y, z, t):
        n = 0.001
        p0 = 1000.
        g = 9.8
        a = 0.01
        return -((n*self.S/self.l)/(self.V*self.p1))*self.dydt(y, z, t) + g*(p0/self.p1 - 1)

    def rungekutta(self, y0, z0, t0, h = 0.01, n = 20):
        ts = np.arange(t0, t0 - n*self.H*h, h)
        vals = [[self.v*t0], [y0], [t0]]

        for t in ts:
            k11 = h*self.dydt(y0, z0, t)
            k21 = h*self.dzdt(y0, z0, t)
            k12 = h*self.dydt(y0+0.5*k11, z0+0.5*k21, t+0.5*h)
            k22 = h*self.dzdt(y0+0.5*k11, z0+0.5*k21, t+0.5*h)
            k13 = h*self.dydt(y0+0.5*k12, z0+0.5*k22, t+0.5*h)
            k23 = h*self.dzdt(y0+0.5*k12, z0+0.5*k22, t+0.5*h)
            k14 = h*self.dydt(y0+k13, z0+k23, t+h)
            k24 = h*self.dzdt(y0+k13, z0+k23, t+h)

            y0 = y0 + (k11+2*k12+2*k13+k14)/6
            z0 = z0 + (k21+2*k22+2*k23+k24)/6

            vals[0].append(self.v*t)
            vals[1].append(y0)
            vals[2].append(t)

            if y0 >= 0: break 

        return vals

    def polynom(self, k, x, y):
        matrix = [[]]
        if ((k > len(x)) or (k > len(y))) and k>0:
            print('fck u')
        else:
            k = k + 1
            for i in range(0, k):
                if i == 0:
                    tmp = [len(x)]
                    for j in range(1, k):
                        tmp.append(np.sum(np.power(x, j)))
                    matrix[0] = tmp
                    matrix[0].append(np.sum(y))
                    continue
                else:
                    tmp = []
                    for j in range(i, k + i):
                        tmp.append(np.sum(np.power(x, j)))
                    matrix.append(tmp)
                    matrix[i].append(np.sum(np.power(x, i) * y))
        return matrix

    def gauss(self, A):
        A = copy.deepcopy(A)
        m = len(A)
        n = m + 1
        
        for k in range(m):
            pivots = [abs(A[i][k]) for i in range(k, m)]
            i_max = pivots.index(max(pivots)) + k
            
            A[k], A[i_max] = A[i_max], A[k]

            for i in range(k + 1, m):
                f = A[i][k] / A[k][k]
                for j in range(k + 1, n):
                    A[i][j] -= A[k][j] * f
                A[i][k] = 0

        x = []
        for i in range(m - 1, -1, -1):
            x.insert(0, A[i][m] / A[i][i])
            for k in range(i - 1, -1, -1):
                A[k][m] -= A[k][i] * x[0]
        return x

    def predict(self, x, coeffs):
        y_pred = coeffs[0]
        for i, a in zip(range(1, len(coeffs[1:]) + 1), coeffs[1:]):
            y_pred += a * (x ** i)
        return y_pred

    def graph(self, vals, vals_pred1, vals_pred2, show = True):
        plt.close('all')
        plt.figure(num='Lab3')
        ax = plt.axes(projection='3d')
        ax.scatter3D(vals[0], vals[2], vals[1], label = 'Runge–Kutta')
        
        ax.plot3D(vals_pred1[2], vals_pred1[0], vals_pred1[1],  color='r', linestyle='dashed', label = 'Approximated trajectory, y = y(t)')
        ax.plot3D(vals_pred2[0], vals_pred2[2], vals_pred2[1],  color='g', linestyle='dashed', label = 'Approximated trajectory, y = y(x)')

        ax.set_xlabel('x')
        ax.set_ylabel('t')
        ax.set_zlabel('y')
        ax.legend()
        if show: plt.show()

if __name__ == '__main__':
    v12 = Lab3()