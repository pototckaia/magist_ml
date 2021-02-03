import numpy as np
import sys

def border_ratio(i, X, y):
    Xii = X[y != y[i]] 
    Xjj = X[y == y[i]]
    x = X[i]

    x1 = Xii[np.argmin(np.linalg.norm(x - Xii, axis=1))]
    x2 = Xjj[np.argmin(np.linalg.norm(x1 - Xjj, axis=1))]

    return np.linalg.norm(x2-x1)/np.linalg.norm(x-x1)



n, m =  map(int, input().split())
data = np.array(list(map(lambda line: list(map(float, line.strip().split())), sys.stdin.readlines())))
X = data[:, :-1]
y = data[:, -1]

for i in range(n): 
    print(f"{border_ratio(i, X, y):0.3f}", end=" ")
