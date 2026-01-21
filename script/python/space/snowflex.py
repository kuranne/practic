def k(n):
    if n > 1:
        return k(n-1) * 4
    return 3

def main():
    print(k(int(input())))
    return 0

if __name__ == "__main__":
    main()