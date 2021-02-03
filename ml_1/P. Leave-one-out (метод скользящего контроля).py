import numpy as np

# integer loo score for predict function
def loo_score(predict, X, y, k):
    e = 0
    for i in range(len(y)):
        yy = predict(
            np.concatenate((X[:i], X[i+1:])), 
            np.concatenate((y[:i], y[i+1:])), 
            X[i], k)
        e += int(y[i] == yy)
    return e