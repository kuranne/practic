quest = list(map(str, input("Enter a text with papaprika effect:").split()))
aeiou = ['a', 'e', 'i', 'o', 'u']
ans = []
def find_alpha(x):
    numsqu = []
    w = 0
    for i in x:
        if i in aeiou:
            numsqu.append(w)
        w+=1
    return numsqu

for i in quest:
    temps = []
    squ = 0
    isp = False
    isn = False
    numsqu = find_alpha(i)
    for j in i:
        if j == 'p' and not isn:
            temps.append(j)
            squ+=1
            continue
        elif j == 'p' and not isp:
            isp = True
            squ += 1
            continue
        elif squ not in numsqu:
            temps.append(j)
        elif not isp and squ in numsqu:
            temps.append(j)
            isn = True
        elif isp and squ in numsqu:
            isp = False
            isn =False
        squ += 1
    ans.append(''.join(temps))

print(' '.join(ans))