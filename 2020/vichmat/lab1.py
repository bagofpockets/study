#v12

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import copy

class Lab1:

    def __init__(self, eta = 0.05, n_iterations = 1000, data = pd.DataFrame({
        'x': [1.577, 1.538, 1.333, 1.847, 1.797, 1.910, 1.371, 1.527, 1.632, 1.034],
        'y': [2.518, 2.390, 2.566, 1.789, 2.069, 1.776, 2.633, 2.136, 2.302, 3.327]}
        )):

        self.data = pd.read_csv('2020\\vichmat\lab1.csv', sep = '|')
        #data.to_csv('study\\2020\\vichmat\lab1.csv', index=False, sep = '|')
        self.x = self.data['x'].values
        self.y = self.data['y'].values
        self.matrix = [[]]
        self.coeffs = []
        self.k = 0

    def polynom(self, k):
        self.k = k
        if ((k > len(self.x)) or (k > len(self.y))) and k>0:
            print('fck u')
        else:
            k = k + 1
            for i in range(0, k):
                if i == 0:
                    tmp = [len(self.x)]
                    for j in range(1, k):
                        tmp.append(np.sum(np.power(self.x, j)))
                    self.matrix[0] = tmp
                    self.matrix[0].append(np.sum(self.y))
                    continue
                else:
                    tmp = []
                    for j in range(i, k + i):
                        tmp.append(np.sum(np.power(self.x, j)))
                    self.matrix.append(tmp)
                    self.matrix[i].append(np.sum(np.power(self.x, i) * self.y))
        return self.matrix

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
        self.coeffs = x
        return x

    def predict(self, x):
        y_pred = self.coeffs[0]
        for i, a in zip(range(1, len(self.coeffs[1:]) + 1), self.coeffs[1:]):
            y_pred += a * (x ** i)
        return y_pred

    def graph(self, show = True):
        y_pred = []
        for i in self.x:
            y_pred.append(self.predict(i))
        self.data['y_pred'] = y_pred
        
        x_pred = np.linspace(min(self.x) - 0.5, max(self.x) + 0.5, 100)
        y_pred = []
        for i in x_pred:
            y_pred.append(self.predict(i))
        
        print('Matrix\n', np.array(self.matrix))
        self.coeffs.reverse()
        print('Coeffs\n', np.array(self.coeffs))
        
        plt.close('all')
        plt.scatter(self.x, self.y, label = 'Data')
        plt.plot(x_pred, y_pred, color='r', label = 'Regression line, k=' + str(self.k))
        plt.xlabel('x')
        plt.ylabel('y')
        plt.legend()
        if show: plt.show()

v12 = Lab1()
v12.gauss(v12.polynom(1))
v12.graph()