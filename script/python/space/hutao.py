def main():
    hp = 100
    i = 0
    while hp > 1:
        hp *= 0.7
        i += 1
    print(i)

if __name__ == "__main__":
    main()