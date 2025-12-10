def a(n):
    if n == 1:
        return 1
    elif n == 2:
        return 3
    elif n > 2:
        return a(n-1) + a(n-2)

print(a(5)) 