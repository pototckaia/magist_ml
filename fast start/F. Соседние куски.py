
n = int(input())
for _ in range(n):
    input()
    diffBoard = 0
    for _ in range(32):
        pic = list(map(int, input().split()))
        diffBoard += abs(pic[31] - pic[32])
    
    print(1 if diffBoard <= 125 else 0)
