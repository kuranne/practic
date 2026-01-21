lenge = int(input())
maxi, minni = None, None

for i in range(lenge):
    something = int(input())
    if i == 0:
        maxi, minni = something, something
        continue
    if maxi < something:
        maxi = something
    if minni > something:
        minni = something

print(f"{minni}\n{maxi}")
    