import sys
input = sys.stdin.readline
readStr  = lambda: input().rstrip('\r\n')
readInt  = lambda: int(input())
readInts = lambda: list(map(int, input().split()))

from decimal import *
getcontext().prec = 50  # precision
x = Decimal(str(x))
y = Decimal("6.7")
x *= y
print(x.quantize(Decimal("0.000001"), rounding=ROUND_HALF_EVEN))
# ROUND_CEILING  : To INF           (2.9 -> 3, -2.1 -> -2)
# ROUND_FLOOR    : To -INF          (2.1 -> 2, -2.9 -> -3)
# ROUND_HALF_EVEN: To nearest even  (2.5 -> 2,  3.5 -> 4)
# ROUND_HALF_UP  : Half away from 0 (2.5 -> 3, -2.5 -> -3)
# ROUND_HALF_DOWN: Half towards 0   (2.5 -> 2, -2.5 -> -2)
# ROUND_UP       : Away from 0      (2.1 -> 3, -2.1 -> -3)
# ROUND_DOWN     : Truncate to 0    (2.9 -> 2, -2.9 -> -2)
# <Default>: ROUND_HALF_EVEN
# <Standard School Math>: ROUND_HALF_UP

