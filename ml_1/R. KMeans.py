import numpy as np
import sys

def kMeans(X, y, n, m, k, t):
    for _ in range(t):
        
        centerCls = []
        for cls in range(k):
            if cls in y:
                centerCls.append(np.mean(X[y == cls], axis=0))
            else:
                centerCls.append(np.zeros(m))
        centerCls = np.array(centerCls)

        old_y = np.copy(y)
        for i in range(n):
            y[i] = np.argmin(np.linalg.norm(centerCls - X[i], axis=1))

        if np.all(old_y == y):
            return y

    return y


n, m, k, t = list(map(int, input().split()))
data = np.array(list(map(lambda line: list(map(float, line.strip().split())), sys.stdin.readlines())))
X = data[:, :-1]
y = data[:, -1].astype(int)

for cl in kMeans(X, y, n, m, k, t): 
    print(f"{cl}")
