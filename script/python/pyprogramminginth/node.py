import sys
def main():
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    n = int(next(it)); m = int(next(it))
    edges = []
    for _ in range(m):
        u = int(next(it)) - 1
        v = int(next(it)) - 1
        d = int(next(it))
        edges.append((d, u, v))
    edges.sort(key=lambda x: x[0])
    parent = list(range(n))
    rank = [0]*n
    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x
    def unite(a,b):
        ra = find(a); rb = find(b)
        if ra == rb: return False
        if rank[ra] < rank[rb]:
            parent[ra] = rb
        else:
            parent[rb] = ra
            if rank[ra] == rank[rb]:
                rank[ra] += 1
        return True

    out_lines = []
    taken = 0
    for d,u,v in edges:
        if unite(u,v):
            out_lines.append(f"{u+1} {v+1}")
            taken += 1
            if taken == n-1:
                break

    out_lines.sort(key = lambda x: int(x[0]))
    sys.stdout.write("\n".join(out_lines))

if __name__ == "__main__":
    main()