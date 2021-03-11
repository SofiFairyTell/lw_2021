# Важная информация! По ссылке объяснение как .py файлы компилировать в .exe
# http://nikovit.ru/blog/samyy-prostoy-sposob-skompilirovat-python-fayl-v-exe/

import ProbabilityTest


# main
def main():
    test = ProbabilityTest.TestForNumbers()
    num = test.set_number()
    print('\n')
    print("Начало выполнения программы")
    while True:
        test_method = int(input("Введите название теста:  "))
        if test_method == 1:
            print("\t\v Тест Ферма")
            test.Ferma_test(num)
        elif test_method == 2:
            print("\t\v Тест Рабина-Миллера'")
            test_num = int(input('Введите число проверок : '))
            test.RabinMiller_test(test_num, num)
        else:
            break


# end main
if __name__ == '__main__':
    main()
