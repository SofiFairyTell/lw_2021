import itertools
import string
import sys

# Важная информация! По ссылке объяснение как .py файлы компилировать в .exe
# http://nikovit.ru/blog/samyy-prostoy-sposob-skompilirovat-python-fayl-v-exe/

# глобальные переменные
alphabet = 'абвгдеёжзийклмнопрстуфхцчшщъьыэюя_,.АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЭЮЯ'


def file_cypher(file_input: str, file_output: str, crypt) -> None:
    with open(file_input) as file_i:
        with open(file_output, "a") as file_o:  # файл для записи
            # content = file_i.readlines()
            line = file_i.readline()
            while line:
                result = crypt(line, 4)
                file_o.write(result)
                line = file_i.readline()
    file_o.close()
    file_i.close()


# Шифр изгороди
"""
    Шифрование: Перемешивает символ строки, помещая 
    каждый из них в сетке (высота зависит от ключа)
    зигзагом формирование и чтение слева направо.
    Дешифрование: Создает шаблон на основе ключа и 
    заполняет его символами входной строки, а затем 
    читает ее в зигзагообразное образование.
"""


def rail_fence_encrypt(input_string: str, key: int) -> str:
    grid = [[] for _ in range(key)]  # лист для сетки с количестом столбцов от key
    lowest = key - 1

    if key <= 0:
        raise ValueError("Height of grid can't be 0 or negative")
    if key == 1 or len(input_string) <= key:
        return input_string

    for position, character in enumerate(input_string):
        num = position % (lowest * 2)  # puts it in bounds
        num = min(num, lowest * 2 - num)  # creates zigzag pattern
        grid[num].append(character)
    grid = ["".join(row) for row in grid]
    output_string = "".join(grid)

    return output_string


def rail_fence_decrypt(input_string: str, key: int) -> str:
    grid = []  # сетка для заполнения полученными символами
    lowest: int = key - 1

    if key <= 0:
        raise ValueError("Height of grid can't be 0 or negative")
    if key == 1:
        return input_string

    temp_grid = [[] for _ in range(key)]  # создаем шаблон на основе ключа
    for position in range(len(input_string)):
        num = position % (lowest * 2)  # puts it in bounds
        num = min(num, lowest * 2 - num)  # creates zigzag pattern
        temp_grid[num].append("*")

    counter = 0
    for row in temp_grid:  # fills in the characters
        splice = input_string[counter: counter + len(row)]
        grid.append([character for character in splice])
        counter += len(row)

    output_string = ""  # reads as zigzag
    for position in range(len(input_string)):
        num = position % (lowest * 2)  # puts it in bounds
        num = min(num, lowest * 2 - num)  # creates zigzag pattern
        output_string += grid[num][0]
        grid[num].pop(0)
    return output_string


# main
def main():
    print("Начало выполнения программы")
    while True:
        # mess = input("Сообщение:  ")
        cypher_method = int(input("Введите номер метода шифрования:  "))
        # filename_input = input("Имя файла для шифрования:")
        # filename_output = input("Имя для зашифрованного файла:")
        filename_i = "..\\lw_2\input.txt"
        filename_o = "..\\lw_2\output.txt"
        filename_o_d = "..\\lw_2\out_d.txt"

        if cypher_method == 1:
            print("\t\vШифр : 'Железнодорожная изгородь'")
            file_cypher(filename_i, filename_o, rail_fence_encrypt)
            # filename_input = input("Имя зашифрованного файла:")
            # filename_output = input("Имя для дешифрованного файла:")
            file_cypher(filename_o, filename_o_d, rail_fence_decrypt)

            # print("Ваше зашифрованное сообщение:  {}".format(result))
        elif cypher_method == 2:
            print("Ваше зашифрованное сообщение:  {}".format())
            print("Ваше исходное сообщение:  {}".format())
        elif cypher_method == 3:
            print("Ваше зашифрованое сообщение:  {}".format())
            print("Ваше исходное сообщение:  {}".format())
        else:
            break


# end main


if __name__ == '__main__':
    main()
