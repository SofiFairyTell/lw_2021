import os
import random
import sys

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

def makeKeyFiles(name: str, keySize: int) -> None:
    if os.path.exists("%s_pubkey.txt" % (name)) or os.path.exists(
        "%s_privkey.txt" % (name)
    ):
        print("\nWARNING:")
        print(
            '"%s_pubkey.txt" or "%s_privkey.txt" already exists. \n'
            "Use a different name or delete these files and re-run this program."
            % (name, name)
        )
        sys.exit()

    publicKey, privateKey = generateKey(keySize)
    print("\nWriting public key to file %s_pubkey.txt..." % name)
    with open("%s_pubkey.txt" % name, "w") as out_file:
        out_file.write(f"{keySize},{publicKey[0]},{publicKey[1]}")

    print("Writing private key to file %s_privkey.txt..." % name)
    with open("%s_privkey.txt" % name, "w") as out_file:
        out_file.write(f"{keySize},{privateKey[0]},{privateKey[1]}")