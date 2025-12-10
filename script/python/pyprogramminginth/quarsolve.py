x,y,z = map(int, input("Input the สมการกำลังสอง here: ").split())
d = 0
for a in range(1, abs(x)+1):
    if x % a != 0:
        continue
    c = x//a
    for b in range(-abs(z), abs(z)+1):
        if b != 0:
            if z % b != 0:
                continue
            d = z//b
            if a*d + c*b == y:
                print(a,b,c,d)
                exit()
print("No Solution")