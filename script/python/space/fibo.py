def fibo(n):
    if n > 1:
        return fibo(n - 1) + n
    else:
        return 1
    
if __name__ == "__main__":
        print(fibo(10))