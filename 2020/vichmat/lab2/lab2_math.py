import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import bisect
import sympy as sm

class Lab2:

    def __init__(self):
        self.shar = False
        self.x = []
        self.y = []
        self.coeffs = []
        self.m = 0.
        self.k = 0.
        self.r0 = 0.
        self.v0 = 0.

    def set_data(self, filename):
        self.data = pd.read_csv(filename, sep = '|')
        if ('x' in self.data.columns) and ('y' in self.data.columns):
            self.shar = False
            self.x = self.data['x'].values
            self.y = self.data['y'].values
        else:
            self.shar = True
            self.m = self.data['m'].values[0]
            self.k = self.data['k'].values[0]
            self.r0 = self.data['r0'].values[0]
            self.v0 = self.data['v0'].values[0]

    def derivatives_polynom(self):
        if self.shar == False:
            bis, cis, dis = [], [], []

            if np.any(np.diff(self.x) < 0):
                indexes = np.argsort(self.x)
                self.x = self.x[indexes]
                self.y = self.y[indexes]

            n = len(self.x)
            his = np.diff(self.x)

            ais = [yi for yi in self.y]

            A = np.zeros((n, n))
            A[0, 0] = 1.0
            for i in range(n - 1):
                if i != (n - 2):
                    A[i + 1, i + 1] = 2.0 * (his[i] + his[i + 1])
                A[i + 1, i] = his[i]
                A[i, i + 1] = his[i]
            A[0, 1] = 0.0
            A[n - 1, n - 2] = 0.0
            A[n - 1, n - 1] = 1.0

            B = np.zeros(n)
            for i in range(n - 2):
                B[i + 1] = 3.0*(ais[i + 2] - ais[i + 1])/his[i + 1] - 3.0*(ais[i + 1] - ais[i])/his[i]
            
            cis = np.linalg.solve(A, B).tolist()

            for i in range(n - 1):
                dis.append((cis[i + 1] - cis[i])/(3.0*his[i]))
                bi = (ais[i + 1] - ais[i])/his[i] - his[i]*(cis[i + 1] + 2.0*cis[i])/3.0
                bis.append(bi)
            
            self.coeffs = [ais, bis, cis, dis]
            return self.coeffs
    
    def calc(self, x):
        if x < self.x[0]:
            return None
        elif x > self.x[-1]:
            return None
        i = bisect.bisect(self.x, x) - 1
        dx = x - self.x[i]
        y = self.coeffs[0][i] + self.coeffs[1][i]*dx + self.coeffs[2][i]*(dx**2.0) + self.coeffs[3][i]*(dx**3.0)
        return y

    def moving_shar(self):
        if self.shar == True:
            omega = sm.sqrt(self.k / self.m)
            A = sm.Symbol('A')
            B = sm.Symbol('B')
            t = sm.Symbol('t')
            rt = A*sm.sin(omega*t) + B*sm.cos(omega*t)
            vt = rt.diff(t)
            rt = sm.lambdify(t, rt)
            vt = sm.lambdify(t, vt)
            solution = sm.solve([rt(0) - self.r0, vt(0) - self.v0])
            rt = solution[A]*sm.sin(omega*t) + solution[B]*sm.cos(omega*t)
            return str(rt)

    def graph(self, show = True):
        plt.close('all')
        plt.figure(num='Lab2')
        plt.scatter(self.x, self.y, label = 'Data')
        
        val_pred = [[], []]
        val_pred[0] = np.arange(min(self.x), max(self.x), 0.01)
        val_pred[1] = [self.calc(x) for x in val_pred[0]]

        plt.plot(val_pred[0], val_pred[1], color='r', linestyle='dashed', label = 'Cubic spline')

        plt.xlabel('x')
        plt.ylabel('y')
        plt.legend()
        if show: plt.show()