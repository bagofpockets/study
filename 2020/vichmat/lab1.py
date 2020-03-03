#v12

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

plt.close('all')
class Lab1:

    def __init__(self, eta = 0.05, n_iterations = 1000, data = pd.DataFrame({
        'x': [1.577, 1.538, 1.333, 1.847, 1.797, 1.910, 1.371, 1.527, 1.632, 1.034],
        'y': [2.518, 2.390, 2.566, 1.789, 2.069, 1.776, 2.633, 2.136, 2.302, 3.327]}
        )):

        self.x = data['x'].values
        self.y = data['y'].values
        self.matrix = [[]]
        

    def polynom(self, k):
        if (k > len(self.x)) or (k > len(self.y)):
            print('f')
        else:
            for i in range(0, k):
                if i == 0:
                    tmp = [k]
                    for j in range(1, k + 1):
                        tmp.append(np.sum(np.power(self.x, j)))
                    self.matrix[0] = tmp
                    self.matrix[0].append(np.sum(self.y))
                    continue
                else:
                    tmp = []
                    for j in range(i, k + i + 1):
                        tmp.append(np.sum(np.power(self.x, j)))
                    self.matrix.append(tmp)
                    self.matrix[i].append(np.sum(np.power(self.x, i)) * np.sum(self.y))
        return self.matrix

    def gauss(self, A):
        n = len(A)

        for i in range(0, n):
            maxEl = abs(A[i][i])
            maxRow = i
            for k in range(i+1, n):
                if abs(A[k][i]) > maxEl:
                    maxEl = abs(A[k][i])
                    maxRow = k

        for k in range(i, n + 1):
            tmp = A[maxRow][k]
            A[maxRow][k] = A[i][k]
            A[i][k] = tmp

        for k in range(i + 1, n):
            c = -A[k][i]/A[i][i]
            for j in range(i, n+1):
                if i == j:
                    A[k][j] = 0
                else:
                    A[k][j] += c * A[i][j]
        
        x = [0 for i in range(n)]
        for i in range(n-1, -1, -1):
            x[i] = A[i][n]/A[i][i]
            for k in range(i-1, -1, -1):
                A[k][n] -= A[k][i] * x[i]
        return x

v12 = Lab1()
print(v12.gauss(v12.polynom(2)))
print(v12.matrix)