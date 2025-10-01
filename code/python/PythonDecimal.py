from decimal import *
getcontext().prec = 500  # precision
getcontext().Emax = 500  # 科學記號指數最大值
# 將東西轉成 Decimal
Decimal(x)
Decimal(y)
Decimal(0.0)
# 運算子跟一般浮點數一樣
x *= y
# 輸出
print(x.quantize(Decimal("0.000001"), rounding=ROUND_HALF_EVEN))
# ROUND_CEILING     (2.9=>3, -2.1=>-2)
# ROUND_FLOOR       (2.1=>2, -2.9=>-3)
# ROUND_HALF_EVEN   (2.5=>2, 3.5=>4)
# ROUND_HALF_UP     (2.5=>3, -2.5=>-3)
# ROUND_HALF_DOWN   (2.5=>2, -2.5=>-2)
# ROUND_UP          (2.1=>3, -2.1=>-3)
# ROUND_DOWN        (2.9=>2, -2.9=>-2)
