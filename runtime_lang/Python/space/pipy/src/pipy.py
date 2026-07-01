n = int(input())
ans = 1
for i in range(1, n+1):
    ans += 1/(i*2+1) if i % 2 == 0 else -1/(i*2+1)

print(ans * 4)