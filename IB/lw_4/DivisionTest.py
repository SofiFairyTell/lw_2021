import  math

import math as math

class DivisionTest:

    def get_factors(number: int) -> list:
        """
        Return the factors of a number.
        :param number: int, positive integer > 1.
        :return: lst, a sorted list of the factors.
        >>> get_factors(2)
        [1, 2]
        >>> get_factors(3)
        [1, 3]
        >>> get_factors(4)
        [1, 2, 4]
        >>> get_factors(100)
        [1, 2, 4, 5, 10, 20, 25, 50, 100]
        """
        if number < 2 or not type(number) == int:
            raise ValueError(f'{number} is invalid. Must be a positive integer > 1.')

        factors = {1, number}
        max_value = int(math.sqrt(number))

        for i in range(2, max_value + 1):
            if number % i == 0:
                factors.add(i)
                factors.add(number // i)

        return sorted(list(factors))
    @classmethod
    def division(cls):
        num = int(input('Введите положительное число больше 1: '))
        if num < 2:
            raise ValueError(f'{num} is invalid. Must be a positive integer > 1.')

        num_factors = cls.get_factors(num)

        if len(num_factors) == 2:
            print(f'{num} это простое число.')
        else:
            print(f'{num} это не простое число для следующих чисел {num_factors}.')