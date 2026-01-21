ans = list(input("Enter a many of A,B or C in single line(don't space)").strip())
n = int(len(ans))
adpat = ['A','B','C']
brupat = ['B','A','B','C']
gopat = ['C','C','A','A','B','B']

scs = {
    "Adrian" : 0,
    "Bruno" : 0,
    "Goran" : 0
}

for i in range(n):
    if adpat[i%3] == ans[i]:
        scs['Adrian']+=1
    if brupat[i%4] == ans[i]:
        scs['Bruno']+=1
    if gopat[i%6] == ans[i]:
        scs['Goran']+=1
        
scs = dict(sorted(scs.items(), key=lambda x: (-x[1],x[0])))
print(max(scs.values()))
for i in scs:
    if scs[i] == max(scs.values()):
        print(i)
