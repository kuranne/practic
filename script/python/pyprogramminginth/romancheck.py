romanint = str(input("Enter Roman Numerals:").upper().strip())
seenchar = []
dupchar = {}

for i in romanint:
    if i not in seenchar:
        seenchar.append(i)
    else:
        if i not in dupchar:
            dupchar[i] = 1
        if i in dupchar:
            dupchar[i] += 1

for i in dupchar:
    if dupchar[i] > 3:
        print('Not Correct')
        break
    else:
        print('Correct')

if len(dupchar) == 0:
    print('Correct')