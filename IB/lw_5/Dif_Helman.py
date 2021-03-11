from random import getrandbits
from random import randint
import sys


class Dif_Helman_cypher:
    # вычисление секретного числа
    @classmethod
    def secret_number_generator(cls):
        big_secret_number = randint(999, 999999)
        return big_secret_number

    # вычисление открытого ключа
    @classmethod
    def key_generator(cls, value, big_secret_number, prime_root):
        public_key = (prime_root**big_secret_number)%value
        return public_key

    # вычисление секретного ключа
    @classmethod
    def secret_key_generator(cls, public_key, big_secret_number, value):
        secret_key = (public_key**big_secret_number)%value
        return secret_key