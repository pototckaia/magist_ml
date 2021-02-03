
a11, a12 = map(float, input().split())
a21 = float(input().split()[0])
al = float(input().strip())


if a12 * a21 == 0:
    print('INF')
elif a11 == al:
    print('NO')
else:
    print('YES')
    print(f'{al + a12 * a21 / (a11 - al):.4f}')
