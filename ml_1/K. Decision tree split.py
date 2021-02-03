import numpy as np
from collections import Counter

# col, row of best split
# X - 2 np.array - train
# Y - 1 np.array class
# criterion - str - 'var', 'gini', 'entropy'
# return index feature and index in train - threshold пороговый
# наилучшее бинарное разделение по правилу x^col <= X[row, col]
def tree_split(X, y, criterion):

    def gini(y):
        p = np.array(list(Counter(y).values())) / len(y)
        return np.sum(p * (1 - p))
    
    def entropy(y):
        p = np.array(list(Counter(y).values())) / len(y)
        return -np.sum(p * np.log(p))


    f = None
    if criterion == 'var':
        f = lambda x: np.var(x) if len(x) > 0 else 0.0
    elif criterion == 'gini':
        f = gini
    elif criterion == 'entropy':
        f = entropy

    featureId = -1
    thresholdId = -1
    bestF = float('inf')
    for col in range(X.shape[1]):
        for row in range(X.shape[0]):
            t = X[:, col] <= X[row, col]
            leftY, rightY = y[t], y[np.invert(t)]

            ff = f(leftY) * len(leftY) + f(rightY) * len(rightY)
            if ff < bestF:
                bestF = ff
                featureId = col
                thresholdId = row
    
    return featureId, thresholdId

# X = np.array([[1, 2, 3], [4, 3, 2], [3, 3, 2]])
# y = np.array([1, 1, 2])
# print(tree_split(X, y, 'entropy'))

