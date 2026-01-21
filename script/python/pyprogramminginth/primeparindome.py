import math

n = int(input())
ans = 0
i = n

def is_prime(n):
    if n % 2 == 0 or n == 1:
        return False
    for i in range(3, int(math.sqrt(n)) + 1, 2):
        if n % i == 0:
            return False
    return True

while True:
    s = str(i)
    if s == s[::-1] and is_prime(i):
        ans = i
        break
    i += 1

print(ans)