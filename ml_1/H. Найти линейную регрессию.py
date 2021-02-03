import numpy as np

# np.array of linear regression coefs
def fit_linear_regression(X, y):
    return np.linalg.inv(X.T @ X) @ X.T @ y