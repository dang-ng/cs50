# TODO

from cs50 import get_float
import math
# while loop
while True:
    answer = get_float("Change owed: ")
    if answer > 0:
        break
# change to cent number
answer *= 100
n = 0
# calculation
n += math.floor(answer/25)
answer %= 25

n += math.floor(answer/10)
answer %= 10

n += math.floor(answer/5)
answer %= 5

n += math.floor(answer/1)
answer %= 1

print(n)
