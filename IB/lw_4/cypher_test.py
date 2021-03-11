# Важная информация! По ссылке объяснение как .py файлы компилировать в .exe
# http://nikovit.ru/blog/samyy-prostoy-sposob-skompilirovat-python-fayl-v-exe/

import ProbabilityTest
import DivisionTest


# main
def main():
    print('\n')
    print("Начало выполнения программы")
    while True:
        test_method = int(input("Введите название теста:  "))
        if test_method == 1:
            print("\t\v Тест Ферма")
            test = ProbabilityTest.TestForNumbers()
            num = test.set_number()
            test.Ferma_test(num)
        elif test_method == 2:
            print("\t\v Тест Рабина-Миллера'")
            test = ProbabilityTest.TestForNumbers()
            num = test.set_number()
            test_num = int(input('Введите число проверок : '))
            test.RabinMiller_test(num, test_num)
        elif test_method == 3:
            print("\t\v Тест на простоту числа")
            DivisionTest.DivisionTest.division()
        else:
            break


# end main
if __name__ == '__main__':
    main()
