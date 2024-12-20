a=[[7,9,3,40,8],[8,5,6,4,5]]
t=[[2,3,1,3],[2,1,2,2]]
e=[2,4]
x=[3,6]
n=5
f=[[0]*n for _ in range(2)]
l=[[0]*n for _ in range(2)]
f[0][0]=e[0]+a[0][0]
f[1][0]=e[1]+a[1][0]

for j in range(1,n):
    for i in range(2):
        if f[i][j-1]+a[i][j]<=f[1-i][j-1]+t[1-i][j-1]+a[i][j]:
            f[i][j]=f[i][j-1]+a[i][j]
            l[i][j]=i
        else:
            f[i][j]=f[1-i][j-1]+t[1-i][j-1]+a[i][j]
            l[i][j]=1-i

f1=f[0][n-1]+x[0]
f2=f[1][n-1]+x[1]

if f1<=f2:
    print(f1)
    i = 0
else:
    print(f2)
    i = 1

path = [i]

for j in range(n-1, 0, -1):
    i = l[i][j]
    path.append(i)
path = list(map(lambda x : x+1, path))

path.reverse()
print("Path:", path)
