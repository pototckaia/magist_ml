import math

def F(x):
    return 8 * math.sin(x) + 7 * x + 5


n = int(input())
f = list(map(float, input().split()))

xl, xr = -1e13, 1e13
while abs(xr - xl) > 2:
    xm = (xr + xl) / 2
    if F(xm) >= f[-1]:
        xr = xm
    else:
        xl = xm
xr = round(xr)

for x in range(xr - 1000, xr + 1000):
    if abs(F(x) - f[-1]) < 1e-5:
        xr = x
        break

print(f"{F(xr + 1):.3f}")