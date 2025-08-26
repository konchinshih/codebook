# Author: Unknown
# Function: Find a non-trivial factor of a big number in O(n^(1/4) log^2(n))
from itertools import count
from math import gcd
from sys import stdin

for s in stdin:
    number, x = int(s), 2
    brk = False
    for cycle in count(1):
        y = x
        if brk:
            break
        for i in range(1 << cycle):
            x = (x * x + 1) % number
            factor = gcd(x - y, number)
            if factor > 1:
                print(factor)
                brk = True
                break
