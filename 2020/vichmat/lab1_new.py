#v12

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

class Lab1:

    def __init__(self, data = pd.DataFrame({
        'x': [1.577, 1.538, 1.333, 1.847, 1.797, 1.910, 1.371, 1.527, 1.632, 1.034],
        'y': [2.518, 2.390, 2.566, 1.789, 2.069, 1.776, 2.633, 2.136, 2.302, 3.327]}
        )):

        self.x = data['x'].values
        self.y = data['y'].values
        self.coefs = []

    def fit(self):
        ones = np.ones(shape = self.x.shape[0]).reshape(-1, 1)
        self.x = np.concatenate((ones, self.x), 1)

        self.coefs = np.linalg.inv(self.x.T.dot(self.x)).dot(self.x.T).dot(self.y)
        

v12 = Lab1()