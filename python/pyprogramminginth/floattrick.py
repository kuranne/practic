n = int(input())
arry = []

for _ in range(n):
    temp = int(input())
    arry.append(2**temp)

print(*arry, sep="\n")