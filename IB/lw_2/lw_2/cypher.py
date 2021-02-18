import itertools
import string
import sys

# Важная информация! По ссылке объяснение как .py файлы компилировать в .exe
# http://nikovit.ru/blog/samyy-prostoy-sposob-skompilirovat-python-fayl-v-exe/

# глобальные переменные
alphabet = 'абвгдеёжзийклмнопрстуфхцчшщъьыэюя_,.'

# main
print("Начало выполнения программы")
while True:
    mess = input("Сообщение:  ")
    cypher_method = int(input("Введите номер метода шифрования:  "))
    if cypher_method == 1:
        print("\t\vШифр :")
    elif cypher_method == 2:
        print("Ваше зашифрованное сообщение:  {}".format())
        print("Ваше исходное сообщение:  {}".format())
    elif cypher_method == 3:
        print("Ваше зашифрованое сообщение:  {}".format())
        print("Ваше исходное сообщение:  {}".format())
    else:
        break

# end main
