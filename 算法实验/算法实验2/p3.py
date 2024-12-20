p = list(input())
n = len(p)
dp = [[0]*n for _ in range(n)]
for i in range(n-1, -1, -1):
    for j in range(i+1, n):
        if p[i] == p[j]:
            dp[i][j] = dp[i+1][j-1]
        else:
            dp[i][j] = min(dp[i+1][j], dp[i][j-1]) + 1
print(dp[0][n-1])
i=0
j=n-1
q=p.copy()
while i<=j:
    if p[i] == p[j]:
        i += 1
        j -= 1
    elif dp[i][j] == dp[i+1][j]+1:
        q.insert(j+1, p[i])
        i += 1
    else:
        j -= 1
        q.insert(i, p[j+1])
print(''.join(q))
