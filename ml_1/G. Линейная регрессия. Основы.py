import numpy as np


# function value
def linear_func(theta, x):
    return x @ theta

# 1-d np.array of function values of all rows of the matrix X
def linear_func_all(theta, X):
    return linear_func(theta, X)

# MSE value of current regression
def mean_squared_error(theta, X, y):
    return np.sum((y - linear_func_all(theta, X))**2 ) / len(y)

# 1-d array of gradient by theta
def grad_mean_squared_error(theta, X, y):
    return -2/len(y)  * (X.T @ (y - X @ theta))
