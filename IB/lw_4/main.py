# Важная информация! По ссылке объяснение как .py файлы компилировать в .exe
# http://nikovit.ru/blog/samyy-prostoy-sposob-skompilirovat-python-fayl-v-exe/

import math as math
import random as random

from past.builtins import xrange


class TestForNumbers:
    number = int()

    def __init__(self):
        pass

    def set_number(self):
        """ Setter for our number """
        self.number = int(input('Введите желаемое число'))
        return self.number

    def Ferma_test(self, number):
        # Входные данные: число number >=5
        # Выходные данные: простое/составное
        # Алгоритм
        """
            1. Выбрать слуйчаное 2<= a< = number -2
            2. Вычислить r = a^(number - 1)(mod number)
            3. Вывод:
                1.  r = 1, number - простое
                2. r != 1 , number - составное"""
        a = random.randint(2, number - 2)
        r = int((a ** (number - 1)) % number)
        if r == 1:
            print("Число {0} простое".format(number))
        else:
            print("Число {0} составное".format(number))
        # Todo

    def toBinary(self, n):
        r = []
        while n > 0:
            r.append(n % 2)
            n = n / 2
            return r

    def RabinMiller_test(self, number, test_step):
        # Входные данные: число number >=5, к-во испытаний - test_step
        # Выходные данные: простое/составное
        # Алгоритм
        """
            1. Представить number - 1 = 2^s r , где r - нечетное
            2. Выбрать случайное целое 2<= a< = number -2
            3. y = a^r(mod n)
            4. y != 1
                1. j = 1,
                2. если j<=s-1 и y != number-1, то y = y^2(mod n)
            4. Вывод:
                1.  y = 1 , number - простое, j = j+1
                2. y != number-1 , number - составное"""
        for j in xrange(1, test_step + 1):
            a = random.randint(1, number - 1)
            b = self.toBinary(number - 1)
            d = 1
            for i in xrange(len(b) - 1, -1, -1):
                x = d
                d = (d * d) % number
                if d == 1 and x != 1 and x != number - 1:
                    return True  # Составное
                if b[i] == 1:
                    d = (d * a) % number
                    if d != 1:
                        return True  # Составное
                    return False  # Простое

    def Partibility_test(self, number) -> str:
        time = ""
        # Todo
        return time


class LargestPrimeNumber:
    def LPN_generator(self, test_step, length_bytes):
        # Todo
        return
