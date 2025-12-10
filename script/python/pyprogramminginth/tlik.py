char = input("Enter a single line of characters(A,B or C): ").strip().upper()
sposi = 1

maps = {
    "A" : {1:2,2:1},
    "B" : {2:3,3:2},
    "C" : {1:3,3:1}
}

for i in char:
    if i in maps:
        sposi = maps[i].get(sposi, sposi)
    else:
        print("Invalid character")
        break

print(sposi)