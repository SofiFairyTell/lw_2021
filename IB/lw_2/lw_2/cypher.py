from random import choice
import itertools
# Важная информация! По ссылке объяснение как .py файлы компилировать в .exe
# http://nikovit.ru/blog/samyy-prostoy-sposob-skompilirovat-python-fayl-v-exe/

# глобальные переменные
from typing import List

alphabet = 'абвгдеёжзийклмнопрстуфхцчшщъьыэюя_,.—АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЭЮЯ'


def file_cypher(file_input: str, file_output: str, crypt, key, mode) -> None:
    key_rail = len(key)  # length of keyword
    key_key = key  # keyword
    if mode == 1:
        with open(file_input) as file_i:
            with open(file_output, "a") as file_o:  # файл для записи
                line = file_i.readline()
                while line:
                    result = crypt(line, key_rail)  # для первого метода
                    file_o.write(result)
                    line = file_i.readline()
    elif mode == 2:
        with open(file_input) as file_i:
            with open(file_output, "a") as file_o:  # файл для записи
                line = file_i.readline()
                while line:
                    result = crypt(line, key_key)  # для второго метода
                    file_o.write(result + "\n")
                    line = file_i.readline()
    file_o.close()
    file_i.close()


class RailFence:
    # Шифр изгороди
    """
        Шифрование: Перемешивает символ строки, помещая
        каждый из них в сетке (высота зависит от ключа)
        зигзагом формирование и чтение слева направо.
        Дешифрование: Создает шаблон на основе ключа и
        заполняет его символами входной строки, а затем
        читает ее в зигзагообразное образование.
    """

    def rail_fence_encrypt(self, input_string: str, key: int) -> str:
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

    def rail_fence_decrypt(self, input_string: str, key: int) -> str:
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


# http://www.crypto-it.net/eng/simple/columnar-transposition.html

class KeyCypher:
    #     encrypt
    def encrypt(self, input_text, keyword) -> str:
        matrix = self.create_matrix(len(keyword), input_text)
        keyword_sequence = KeyCypher.get_sequence(keyword)

        ciphertext = ""
        for num in range(len(keyword_sequence)):
            pos = keyword_sequence.index(num + 1)
            for row in range(len(matrix)):
                if len(matrix[row]) > pos:
                    ciphertext += matrix[row][pos]
        return ciphertext

    # создадим матрицу из полученной строки
    @staticmethod
    def create_matrix(width, message: str):
        r = 0
        c = 0
        matrix = [[]]
        for pos, ch in enumerate(message):
            matrix[r].append(ch)
            c += 1
            if c >= width:
                c = 0
                r += 1
                matrix.append([])
        return matrix

    # decrypt
    def decrypt(self, message, keyword):
        matrix = self.decryption_matrix(self.get_sequence(keyword), message)
        plaintext = ""
        for r in range(len(matrix)):
            for c in range(len(matrix[r])):
                plaintext += matrix[r][c]
        return plaintext

    def decryption_matrix(self, keyword_sequence, message):
        width = len(keyword_sequence)
        height = int(len(message) / width)
        if height * width < len(message):
            height += 1
        matrix = self.create_empty(width, height, len(message))
        pos = 0
        for num in range(len(keyword_sequence)):
            column = keyword_sequence.index(num + 1)
            row = 0
            while (row < len(matrix)) and (len(matrix[row]) > column):
                matrix[row][column] = message[pos]
                row += 1
                pos += 1
        return matrix

    @staticmethod
    def create_empty(width, height, length):
        matrix = []
        total_added = 0
        for r in range(height):
            matrix.append([])
            for c in range(width):
                if total_added >= length:
                    return matrix
                matrix[r].append('')
                total_added += 1
        return matrix

    # получим из введенного ключевого слова последовательноть цифр
    # первой в последовательности будет цифра наиболее близкая к началу алфавита
    # следующая по порядку будет второй и т.д.
    @staticmethod
    def get_sequence(keyword):
        sequence = []
        for pos, ch in enumerate(keyword):
            previous_letters = keyword[:pos]
            new_number = 1
            for previousPos, previousCh in enumerate(previous_letters):
                if previousCh > ch:
                    sequence[previousPos] += 1
                else:
                    new_number += 1
            sequence.append(new_number)
            print(sequence)
        return sequence


class KeySearch:
    # из доступного алфавита генерирует последовательность символов, которые могут быть использованы в качестве ключа
    def generator(len: int) -> str:
        out = ''.join(choice(alphabet) for i in range(len))
        return out


# main
def main():
    print("Начало выполнения программы")
    while True:
        # mess = input("Сообщение:  ")
        cypher_method = int(input("Введите номер метода шифрования:  "))
        directory = input("Имя директорию для файлов шифрования:")
        filename = input("Имя файла для шифрования [\<имя файла>]:")
        # filename_o = input("Имя для зашифрованного файла:")
        # filename_o_d = input("Имя для расшифрованного файла:")
        filename_i = directory + filename
        filename_o = directory +"\output.txt"
        filename_o_d = directory + "\out_d.txt"
        # filename_i = "..\\lw_2\input.txt"
        # filename_o = "..\\lw_2\output.txt"
        filename_t = "..\\out_temp.txt"
        filename_t2 = "..\\out_temp2.txt"
        # filename_o_d = "..\\out_d.txt"
        filename_o_d2 = "..\\out_d2.txt"

        if cypher_method == 1:
            print("\t\vШифр : 'Железнодорожная изгородь'")
            rail_fence = RailFence()
            key_len = input("Введите ключ:  ")
            file_cypher(filename_i, filename_o, rail_fence.rail_fence_encrypt, key_len, 1)

            file_cypher(filename_o, filename_o_d, rail_fence.rail_fence_decrypt, key_len, 1)

            # print("Ваше зашифрованное сообщение:  {}".format(result))
        elif cypher_method == 2:
            print("\t\vШифр : 'Перестановка с ключом'")
            crypt = KeyCypher()
            key_len = input("Введите ключ:  ")
            file_cypher(filename_i, filename_o, crypt.encrypt, key_len, 2)
            # print("Ваше зашифрованное сообщение:  {}".format())
            # print("Ваше исходное сообщение:  {}".format())
            file_cypher(filename_o, filename_o_d, crypt.decrypt, key_len, 2)
        elif cypher_method == 3:
            print("\t\vШифр : 'Комбинированный шифр'")
            crypt = RailFence()
            crypt2 = KeyCypher()
            key_len = input("Введите ключ:  ")
            file_cypher(filename_i, filename_t, crypt.rail_fence_encrypt, key_len, 1)
            file_cypher(filename_t, filename_o, crypt2.encrypt, key_len, 2)
            # дешифровка
            file_cypher(filename_o, filename_t2, crypt2.decrypt, key_len, 2)
            file_cypher(filename_t2, filename_o_d2, crypt.rail_fence_decrypt, key_len, 1)

            # print("Ваше зашифрованое сообщение:  {}".format())
            # print("Ваше исходное сообщение:  {}".format())
        elif cypher_method == 4:
            crypt = KeyCypher()
            with open(filename_i) as file_i:
                line = file_i.readline()
            file_i.close()
            key_len = int(input("Введите длину ключа:  "))
            for i in range(1, key_len, 1):
                key = KeySearch.generator(i)
                perm = itertools.permutations(key)
                for j in list(perm):
                    file_cypher(filename_i, filename_o, crypt.encrypt, j, 2)
                # file_cypher(filename_o, filename_o_d, crypt.decrypt, key, 2)
        else:
            break


# end main
if __name__ == '__main__':
    main()
