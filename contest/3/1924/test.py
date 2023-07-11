from math import sqrt

M = 11653310467824836911
m = int(sqrt(M))
print(m)

for i in range(2, m + 1):
    if (M % i == 0):
        print(i, M / i)
    if (i % 10000000 == 0):
        print(i)