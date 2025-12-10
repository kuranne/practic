a, b, c = map(int, input("Three number (Split): ").split())
if c - b >= b - a:
    print(c-b-1)
else:
    print(b-a-1)