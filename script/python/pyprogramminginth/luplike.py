n = int(input("Enter the number for next amount: "))
lupelike = list(map(int, input().split()))
winn = []

luplike = []
if len(lupelike) != n:
    raise TypeError("Input length does not match the specified number of elements.")
for i in lupelike:
    if i not in luplike:
        winn.append({"nums": i, "count": 1})
        luplike.append(i)
    else:
        for j in winn:
            if j["nums"] == i:
                j["count"] += 1
                break

winn.sort(key=lambda x: (-x["count"], x["nums"]))
forwinn = winn[0]["count"]
printswin = []
for i in winn:
    if i["count"] == forwinn:
        printswin.append(i["nums"])
print(" ".join(map(str, printswin)))
