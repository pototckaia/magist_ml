import numpy as np


# array of pairs -- class and number of votes of neighbors
def knn_predict_simple(X, y, x, k):
    ii = np.argsort(np.linalg.norm(X - x, axis=1))
    cls, voices = np.unique(y[ii[:k]], return_counts=True)
    return list(zip(cls, voices))
