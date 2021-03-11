import math
import Dif_Helman

class Input:
    @staticmethod
    def count_digits(n):
        if n == 0:
            return 0
        return 1 + n.count_digits(n // 10)

    @staticmethod
    def binary_input():
        binary = int(input("Введите число в двоичном виде (до 10 символов): "),2)
        try:
             binary == 0
        except Warning:
               print("Число слишком мало! Необходимо вводить числа строго больше нуля!")
        else:
            print("Необходимо вводить число только в двоичном виде!")
        try:
            digits = int(math.log10(binary)) + 1 > 10 # Проверяем если введенное число больше 10 значеиний
        except IndexError:
            print("Число слишком большое")
        return binary

    @staticmethod
    def decimal_input():
        decimal = int(input("Введите число в десятичном виде : "))
        try:
            decimal == 0
        except Warning:
            print("Число слишком мало! Необходимо вводить числа строго больше нуля!")
        except ValueError:
            print("Нужно вводить только числа")
        return decimal

    @staticmethod
    def hex_input():
        num = input("Введите 16 - ричное число :  ")
        try:
            hex = int(num, 16)  # interpret the input as a base-16 number, a hexadecimal.
        except ValueError:
            print("Вы не ввели 13-ричное число")
        return  hex

    @staticmethod
    def convert_binary_to_decimal(value):
      return int(value,2)

    @staticmethod
    def convert_hex_to_binary(value):
        return int(value,16)

class Prime:
    def __init__(self):
        pass

    @staticmethod
    def GCD(a,b): #НОД
        while a!=b:
            if a>b:
                a = a-b
            else:
                b = b - a
        return a
    # проверка на простоту тут  и на первообразность
    @staticmethod
    # Возврат первообразного корня для введенного числа
    def prime_root(value):
      required_set = set(num for num in range(1,value) if Prime.GCD(num,value)==1)
      for g in range(1,value):
          real_set = set(pow(g,powers)%value for powers in range(1,value))
          if required_set == real_set:
              return g

#вызов метода шифрования для создания 2-х ключей
def cypher_method(prime_root,dec_convert):
    # публичный ключ для первого
    secret_number_A = Dif_Helman.Dif_Helman_cypher.secret_number_generator()
    public_key_A = Dif_Helman.Dif_Helman_cypher.key_generator(dec_convert,secret_number_A,prime_root)

    # публичный ключ для второго
    secret_number_B = Dif_Helman.Dif_Helman_cypher.secret_number_generator()
    public_key_B = Dif_Helman.Dif_Helman_cypher.key_generator(dec_convert,secret_number_B,prime_root)

    # секретный ключ для первого
    private_key_A = Dif_Helman.Dif_Helman_cypher.secret_key_generator(public_key_B,secret_number_A,dec_convert)
    private_key_B = Dif_Helman.Dif_Helman_cypher.secret_key_generator(public_key_A,secret_number_B,dec_convert)

    print("первый ключ {0} второй ключ: {1}".format(public_key_A,public_key_B))


# вопрос для пользователя
def question(prime_root,dec_convert):
   answer = input("Создать секретный ключ c полученным числом?")
   if answer == "да":
      cypher_method(prime_root,dec_convert)
      return True
   return False

def main():
    print('Start')
    while True:
        menu = int(input('Введите 2, 10, 16 для начала ввода'))
        if menu == 2:
         dec_convert =  Input.convert_binary_to_decimal(Input.binary_input())
         prime_root = Prime.prime_root(dec_convert)
         print("Простое корень: {0}".format(prime_root))
         question(prime_root,dec_convert )
        elif menu == 10:
          dec_convert =  Input.decimal_input()
          prime_root = Prime.prime_root(dec_convert)
          print("Простое корень: {0}".format(prime_root))
          question(prime_root, dec_convert)
        elif menu == 16:
          dec_convert = Input.convert_hex_to_binary(Input.hex_input())
          prime_root = Prime.prime_root(dec_convert)
          print("Простое корень: {0}".format(prime_root))
          question(prime_root,dec_convert)
        else:
            break

if __name__ == '__main__':
    main()