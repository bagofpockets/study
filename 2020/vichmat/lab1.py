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

    def linear_regression(self):
        x_mean = np.mean(self.x)
        y_mean = np.mean(self.y)
        n = len(self.x)

        numerator = 0
        denominator = 0
        for i in range(n):
            numerator += (self.x[i] - x_mean) * (self.y[i] - y_mean)
            denominator += (self.x[i] - x_mean) ** 2
            
        b1 = numerator / denominator
        b0 = y_mean - (b1 * x_mean)

        x_max = np.max(self.x) + 0.1
        x_min = np.min(self.x) - 0.1
        x = np.linspace(x_min, x_max, 1000)
        y = b0 + b1 * x - 0.03 *(x ** 2)
        
        plt.close('all')
        plt.plot(x, y, color='#00ff00', label='Linear Regression')
        plt.scatter(self.x, self.y, color='#ff0000', label='Data Point')
        plt.xlabel('x')
        plt.ylabel('y')
        plt.legend()
        plt.show()

        
        '''
        data_series = pd.Series([[1.577, 2.518], 
                                 [1.538, 2.390], 
                                 [1.333, 2.566], 
                                 [1.847, 1.789], 
                                 [1.797, 2.069], 
                                 [1.910, 1.776], 
                                 [1.371, 2.633], 
                                 [1.527, 2.136], 
                                 [1.632, 2.302], 
                                 [1.034, 3.327]],
                                 name = "dots")

        self.eta = eta
        self.n_iterations = n_iterations
        self.data = data
        self.data.index.name = 'id'

    def fit(self):
        iadarr = self.data.index.to_numpy()
        self.w_ = np.zeros((iadarr.reshape((iadarr.shape[0], 1))
                                            .shape[1], 1))
        self.cost_ = []
        m = iadarr.shape[0]
        x = self.data.x.to_numpy()
        x = x.reshape((x.shape[0], 1))
        y = self.data.y.to_numpy()
        y = y.reshape((y.shape[0], 1))

        for _ in range(self.n_iterations):
            y_pred = np.dot(x, self.w_)
            residuals = y_pred - y
            gradient_vector = np.dot(x.T, residuals)
            self.w_ -= (self.eta / m) * gradient_vector
            cost = np.sum((residuals ** 2)) / (2 * m)
            self.cost_.append(cost)
        return self

    def predict(self, x):
        return np.dot(x, self.w_[0,0])
#print(data['x'][0])
#print(data['y'][0])
#print(max(data.index))
#print(max(data['x']))
#data['a'] = data.y/data.x
#print(data.sort_values(by=['a'], ascending=False))
'''

if __name__ == "__main__":
    v12 = Lab1()
    v12.do_the_lab()
    '''
    v12.fit()
    v12.data['yw'] = v12.w_[0,0] * v12.data['y']
    print(v12.data)
    ax = plt.gca()
    #v12.data.plot.scatter(x = 'x', y = 'y', ax = ax)
    v12.data.plot.scatter(x = 'x', y = 'y', ax = ax)
    v12.data.plot.scatter(x = 'x', y = 'yw', ax = ax, color='k')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.show()
    '''
