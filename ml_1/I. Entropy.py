import numpy as np
from collections import Counter

# entropy value for labels -- y
def entropy(y):
    p = np.array(list(Counter(y).values())) / len(y)
    return -np.sum(p * np.log(p))
