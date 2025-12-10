n = int(input("Number of ingredients: "))
s, b = [], []
for i in range(n):
    temps = input(f"Number {i+1} Sour and Bitt(Split): ").split()
    s.append(int(temps[0]))
    b.append(int(temps[1]))

def calsandb (count, c, sour, bitt):
    if c == n:
        if count > 0: return abs(sour - bitt)
        else: return 1e9
    return min([calsandb(count + 1, c + 1, sour * s[c], bitt + b[c]), calsandb(count, c + 1, sour, bitt)])

print(calsandb(0, 0, 1, 0))