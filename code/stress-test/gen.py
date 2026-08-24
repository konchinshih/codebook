from random import *
n = randint(1, 10)
arr = list(randint(1, 20) for i in range(n))
print(*arr)
# permutation / non-repetitive sequence
perm = sample(range(1, n + 1), n)
arr = sample(range(1, 10000 + 1), n)
# string
from string import *
s = "".join(choices(ascii_lowercase, k=n))
t = "".join(choices(ascii_lowercase[:3], k=n))  # (a|b|c)*
u = "".join(choices(ascii_lowercase + ascii_uppercase + digits, k=n))
# palindrome
half = "".join(choices(ascii_lowercase, k=(n + 1) // 2))
palindrome = half + (half[-2::-1] if n % 2 else half[::-1])
# ================== tree ================== 
n = 30
## shallow tree
edges = [(randint(1, u - 1), u) for u in range(2, n + 1)]
## deep tree
## (suggested k: 2 ~ 5 or int(sqrt(n)) or 2n/D (D is expected depth))
from math import *
k = int(sqrt(n))
edges = [(randint(max(1, u-k), u-1), u) for u in range(2, n + 1)]
for e in edges:
    print(*e)

edges = [(1, i) for i in range(2, n + 1)]  ## star
edges = [(i, i + 1) for i in range(1, n)]  ## chain
edges = [(i // 2, i) for i in range(2, n + 1)]  ## complete binary tree
# ================== graph ================== 
## not necessarily connected, no multi-edge or self-loop
n = 10
density = 0.3  # graph density (0.0 ~ 1.0)
edges = [(i, j) for i in range(1, n+1) for j in range(i+1, n+1) if random() < density]
## connected, no multi-edge or self-loop
n, extra_edges = 10, 5
edges = set()
#### ... generate spanning tree with codes above
while len(edges) < n - 1 + extra_edges:
    u, v = randint(1, n), randint(1, n)
    if u != v:
        edges.add((min(u, v), max(u, v)))
edges = list(edges)
## DAG
perm = sample(range(1, n + 1), n)
edges = []
for _ in range(m):
    i, j = sorted(sample(range(n), 2))
    edges.append((perm[i], perm[j]))
## Bipartite Graph
n1, n2 = 6, 7
left, right = list(range(1, n1+1)), list(range(n1+1, n1+n2+1))
edges = [(choice(left), choice(right)) for _ in range(m)]
