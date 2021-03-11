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

    @staticmethod
    def Ferma_test(number):
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

    def RabinMiller_test(self, num, test_step):
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
        if num == 2:
            print("True")
        if num % 2 == 0:
            print("False")
        r, s = 0, num - 1
        while s % 2 == 0:
            r += 1
            s //= 2
            for _ in range(test_step):
                a = random.randrange(2, num - 1)
                x = pow(a, s, num)
            if x == 1 or x == num - 1:
                continue
            for _ in range(r - 1):
                x = pow(x, 2, num)
                if x == num - 1:
                    break
            else:
                print('Число {0} вероятно простое'.format(num))
        print('Число {0} составное'.format(num))
