# Важная информация! По ссылке объяснение как .py файлы компилировать в .exe
# http://nikovit.ru/blog/samyy-prostoy-sposob-skompilirovat-python-fayl-v-exe/

import math as math
import random as random


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
        a = random.randint(2, number-2)
        r = int((a**(number - 1)) % number)
        if r == 1:
            print("Число {0} простое".format(number))
        else:
            print("Число {0} составное".format(number))
        # Todo

    def RabinMiller_test(self, number, test_step):
        if (number):
            print("Задано количество проверок")
            # Todo

    def Partibility_test(self, number) -> str:
        time = ""
        # Todo
        return time


class LargestPrimeNumber:
    def LPN_generator(self, test_step, length_bytes):
        # Todo
        return
