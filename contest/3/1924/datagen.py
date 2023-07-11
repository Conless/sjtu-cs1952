from Crypto.Util import number

p = 3180480461
q = 3664009451
N = p * q
e = 65537
phi = (p - 1) * (q - 1) // 4

# https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Computing_multiplicative_inverses_in_modular_structures
# https://zh.wikipedia.org/wiki/%E6%A8%A1%E5%8F%8D%E5%85%83%E7%B4%A0
d = number.inverse(e, phi)

m = 2387268731397292364
sig = pow(m, d, N)
ver = pow(sig, e, N)

print(N)  # 11653310467824836911
print(sig)
print(ver)
print(ver == m)  # True
