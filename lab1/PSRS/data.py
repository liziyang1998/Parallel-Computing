import os
import sys
import random

f = open('1.txt', 'w')
sum = 10000000
f.write(str(sum) + '\n')
for i in range(sum):
    f.write(str(random.randint(1, sum)) + ' ')
    # print(random.randint(1, sum), end = ' ')
