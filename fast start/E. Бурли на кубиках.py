import math

n, k = list(map(int, input().split()))

c = (-1) * (k-1)**n
for i in range(1, n+1):
    b = math.factorial(n) / (math.factorial(i) * math.factorial(n - i))
    c += i * b * (k - 1)**(n - i)
c /= k ** n
print(f"{c:.5f}")
