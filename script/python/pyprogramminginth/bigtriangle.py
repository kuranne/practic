n = int(input())
inputtemps = []
macresult = None

for _ in range(n):
   a, b = map(int, input().split())
   #a, b = _, _+1
   inputtemps.append((a,b))

for i in range(n):
    for j in range(i+1, n):
        for k in range(j+1, n):
            a = inputtemps[i]
            b = inputtemps[j]
            c = inputtemps[k]

            if a != b and b!=c and c!=a:
                result = abs(a[0]*b[1]+b[0]*c[1]+c[0]*a[1]-(a[1]*b[0]+b[1]*c[0]+c[1]*a[0]))/2

            if not macresult or result > macresult:
                macresult = result

print(f"{macresult:.3f}")