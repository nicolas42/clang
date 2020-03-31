from ctypes import *

lib = CDLL("main.so", RTLD_GLOBAL)

print(lib.test(3))

print(lib.is_prime(5))
