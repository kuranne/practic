nugget = [6, 9, 20]
ans = []
check = True

n = int(input())

while n >= 6 and check:
    check = False
    for i in nugget:
        if 1080 % i == 0:
            if n % i == 0:
                ans.append(i)
                n -= i
                check = True
                break

if sum(ans) != 0:
    ans.sort()
    temp = 0
    for i in ans:
        print(i + temp)
        temp += i
else:
    print("none")