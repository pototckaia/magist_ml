import math

x1, y1, x2, y2 = list(map(float, input().split()))

c = math.sqrt(2) / 2
ans = math.fabs(((x2 - x1) - (y2 - y1)) * c) +\
    math.fabs(((x2 - x1) + (y2 - y1)) * c)
print(f"{ans:.5f}")
