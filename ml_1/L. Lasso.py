import numpy as np
from sklearn import linear_model

def lasso(x, y, k, s):
    left, right = 0, 100
    eps = 1e-6

    while(right - left >= eps):
        mid = (left + right) / 2

        las = linear_model.Lasso(alpha=mid, max_iter=100000)
        las.fit(x, y)

        r2_score = las.score(x, y)
        n_zeros = list(las.coef_).count(0.0)
        if n_zeros == k and r2_score >= s:
            # print(las.coef_, las.intercept_)
            print(mid, las.coef_.shape, r2_score, n_zeros)
            return list(las.coef_) + [las.intercept_]

        if n_zeros > k:
            right = mid
        else:
            left = mid

    return [0 for i in range(x.shape[0] + 1)]

if __name__ == "__main__":
    with open("train_lasso.txt") as fin, open("output.txt", "w") as fout:
        N = int(fin.readline())
        for _ in range(N):
            n, m, k, s = list(map(float, fin.readline().split()))
            n, m, k = int(n), int(m), int(k)
            print(n, m, k, s)

            x, y = np.zeros((n, m)), np.zeros(n)
            for i in range(n):
                line = list(map(float, fin.readline().split()))
                x[i, :] = line[:-1]
                y[i] = line[-1]

            # print(x)
            # print(y)
            a = lasso(x, y, k, s)
            fout.write(" ".join([f"{x}" for x in a]) + "\n")