import numpy as np
from collections import Counter

# gini value for labels -- y
def gini(y):
    p = np.array(list(Counter(y).values())) / len(y)
    return np.sum(p * (1 - p))