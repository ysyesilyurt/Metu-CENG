#!/usr/bin/env python3

from fractions import gcd

done = False

for i in range(1,14029):
    if done:
        break
    for j in range(1,14029):
        if i == j:
            continue
        else:
            result = (i * j) / gcd(i,j)
            if result == 14030:
                print("your first number:",i,"and your beloved second:",j)
                done = True
                break
