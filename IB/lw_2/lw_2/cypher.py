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
            line = file_i.readline()
            while line:
                # result = crypt(line, 4) # для первого метода
                result = crypt(line, 'сон') # для второго метода
                file_o.write(result)
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
        return sequence


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
            rail_fence = RailFence()
            file_cypher(filename_i, filename_o, rail_fence.rail_fence_encrypt)
            # filename_input = input("Имя зашифрованного файла:")
            # filename_output = input("Имя для дешифрованного файла:")
            file_cypher(filename_o, filename_o_d, rail_fence.rail_fence_decrypt)

            # print("Ваше зашифрованное сообщение:  {}".format(result))
        elif cypher_method == 2:
            crypt = KeyCypher()
            file_cypher(filename_i, filename_o, crypt.encrypt)
            # print("Ваше зашифрованное сообщение:  {}".format())
            # print("Ваше исходное сообщение:  {}".format())
            file_cypher(filename_o, filename_o_d, crypt.decrypt)
        elif cypher_method == 3:
            print("Ваше зашифрованое сообщение:  {}".format())
            print("Ваше исходное сообщение:  {}".format())
        else:
            break


# end main


if __name__ == '__main__':
    main()
