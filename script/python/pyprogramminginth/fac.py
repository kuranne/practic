import math
n = int(input())

if n % 2 == 0:
    result = math.comb(n, n//2)
else:
    result = math.comb(n, math.floor(n/2)) + math.comb(n, math.ceil(n/2))
print(result)