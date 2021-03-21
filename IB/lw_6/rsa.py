import random
import primeNum
from typing import Tuple

def generateKey(keySize: int) -> Tuple[Tuple[int, int], Tuple[int, int]]:
    print("Generating prime p...")
    p = primeNum.generateLargePrime(keySize)
    print("Generating prime q...")
    q = primeNum.generateLargePrime(keySize)
    n = p * q

    print("Generating e that is relatively prime to (p - 1) * (q - 1)...")
    while True:
        e = random.randrange(2 ** (keySize - 1), 2 ** (keySize))
        if primeNum.gcd(e, (p - 1) * (q - 1)) == 1:
            break

    print("Calculating d that is mod inverse of e...")
    d = primeNum.findModInverse(e, (p - 1) * (q - 1))

    publicKey = (n, e)
    privateKey = (n, d)

    return (publicKey, privateKey)