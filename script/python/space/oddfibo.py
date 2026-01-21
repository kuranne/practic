def S(n):
    if n > 1:
        return S(n - 1) + (2 * n - 1)
    else:
        return 1
    
print(S(10))