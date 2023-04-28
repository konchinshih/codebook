from decimal import *
getcontext().prec = 2500000
getcontext().Emax = 2500000
a,b = Decimal(input()),Decimal(input())
a*=b
print(a)