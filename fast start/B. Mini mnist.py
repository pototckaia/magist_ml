n = 28
a = []
dates = [input().rstrip('\n') for i in range(n)]
for line in dates:
    a.append([int(a_i == '#') for a_i in line])

def dfs(d, v, x, y):
    if not(0 <= x < len(d) and 0 <= y < len(d[x]) and d[x][y] == 0):
        return
    d[x][y] = v
    dfs(d, v, x + 1, y)
    dfs(d, v, x, y + 1)
    dfs(d, v, x - 1, y)
    dfs(d, v, x, y - 1)
    
    # dfs(d, v, x + 1, y + 1)
    # dfs(d, v, x - 1, y + 1)
    # dfs(d, v, x - 1, y - 1)
    # dfs(d, v, x + 1, y - 1)

def count_areas(d):
    v = 1
    for x in range(len(d)):
        for y in range(len(d[x])):
            if d[x][y] == 0:
                v += 1
                dfs(d, v, x, y)
    return v - 1

def predict_area(a):
    c = count_areas(a)
    if c >= 3:
        return 8
    if c >= 2:
        return 6
    return 7

digit = predict_area(a)
print(str(digit))

