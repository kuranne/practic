arry, posi = map(int, input("First for lenght and second for position(Space): ").split())
arry+=1
count = 0
realnum = list(range(2,arry))

while count < posi:
    princ = min(realnum)
    realnum.remove(princ)
    count+=1
    thatnum = princ
    if count < posi:
        for i in realnum:
            if i%princ == 0:
                realnum.remove(i)
                count+=1
                thatnum = i
            if count == posi:
                break

print(thatnum)