import itertools
import string
import sys

#Важная информация! По ссылке объяснение как .py файлы компилировать в .exe
#http://nikovit.ru/blog/samyy-prostoy-sposob-skompilirovat-python-fayl-v-exe/

#глобальные переменные
alphabet='абвгдеёжзийклмнопрстуфхцчшщъьыэюя_,.'

#шифр Плейфера
#шаг 1: составление матрицы. Входные данные : алфавит и ключевое слово
#Первая строка заполняется содержимым ключевого слова. 
#Символы не должны повторяться. 
#Остальная часть таблицы - по порядку те буквы алфавита, которых нет в слове. 
def chunker(seq, size):
    it = iter(seq)
    while True:
        chunk = tuple(itertools.islice(it, size))
        if not chunk:
            return
        yield chunk

def my_input(plaintext: str) -> str:
    
	#здесь все буквы сделаем строчными 
    alphabet='абвгдеёжзийклмнопрстуфхцчшщъьыэюя'
	#генерируем список 
    plaintext = "".join([c.lower() for c in plaintext if c in alphabet])
    #срока котору ю вернем для шифра
    plaintext_return = ""
	#не менее 2 символов в строке должно быть
    if len(plaintext) < 2:
        return plaintext
    for i in range(len(plaintext) - 1):
        plaintext_return += plaintext[i]
		#если два символа будут одинаковыми в слове то укажем менее используемый символ
        if plaintext[i] == plaintext[i + 1]:
            plaintext_return += "ё"
    plaintext_return += plaintext[-1]

    if len(plaintext_return) & 1:
        plaintext_return += "ё"

    return plaintext_return

def generate_matrix(key:str)->[str] :
    matrix = [] 

    #alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"
	#Изменим регистр символов в строке
    for char in key.lower():
		#если символа нет в таблице, но он есть в алфавите
		# то добавим его в матрицу
        if char not in matrix and char in alphabet:
           matrix.append(char)
    for char in alphabet:
        if char not in matrix:
           matrix.append(char)
    return matrix

def playfair_encrypt(plaintext:str, key:str)->str:
    table = generate_matrix(key)

    plaintext = my_input(plaintext)

   # print("ТАБЛИЦА ШИФРОВ:{}".format(table))

    ciphertext = ""
    for char1, char2 in chunker(plaintext, 2):
        row1, col1 = divmod(table.index(char1), 6)
        row2, col2 = divmod(table.index(char2), 6)   
        if row1 == row2:
            ciphertext += table[row1 * 6 + (col1 + 1) % 6]
            ciphertext += table[row2 * 6 + (col2 + 1) % 6]
        elif col1 == col2:
            ciphertext += table[((row1 + 1) % 6) * 6 + col1]
            ciphertext += table[((row2 + 1) % 6) * 6 + col2]
        else:  # rectangle
            ciphertext += table[row1 * 6 + col2]
            ciphertext += table[row2 * 6 + col1]

    return ciphertext

def playfair_decode(ciphertext: str, key: str) -> str:
    table = generate_matrix(key)
    plaintext = ""

    # https://en.wikipedia.org/wiki/Playfair_cipher#Description
    for char1, char2 in chunker(ciphertext, 2):
        row1, col1 = divmod(table.index(char1), 6)
        row2, col2 = divmod(table.index(char2), 6)

        if row1 == row2:
            plaintext += table[row1 * 6 + (col1 - 1) % 6]
            plaintext += table[row2 * 6 + (col2 - 1) % 6]
        elif col1 == col2:
            plaintext += table[((row1 - 1) % 6) * 6 + col1]
            plaintext += table[((row2 - 1) % 6) * 6 + col2]
        else:  # rectangle
            plaintext += table[row1 * 6 + col2]
            plaintext += table[row2 * 6 + col1]

    return plaintext


#Аддитивный моноалфавитный шрифт с задаваемым смещением
def cesar_encrypt(input_str:str, shift:int)->str:
	encrypted_message = ""

	for char in input_str:
		if char not in alphabet:
			encrypted_message += char
		else:
			new_key = (alphabet.index(char) + shift) % len(alphabet)
			#Добавим закодированный символ 
			encrypted_message += alphabet[new_key]		

	return encrypted_message

def cesar_decrypt(input_string: str, key: int) -> str:
    key *= -1
    return cesar_encrypt(input_string, key)

#Мультипликативный моноалфавитный шрифт с задаваемым смещением (Афинный шифр)

#Функция для поиска наименьшего общего делителя GCD
def gcd(a: int, b: int) -> int:
    while a != 0:
        a, b = b % a, a
    return b

#TIPS: В модульной арифметике каждое целое число имеет аддитивную инверсию. 
#Сумма целого числа и его аддитивной инверсии сравнима с 0 по модулю n .
#В модульной арифметике целое число может или не может иметь мультипликативную инверсию. 
#Целое число и его мультипликативная инверсия сравнимы с 1 по модулю n .

#Ищем здесь k^-1
#оптимально, если вернется 1
def findModInverse(a: int, m: int) -> int:
    if gcd(a, m) != 1:#это означает, что a и m не взаимно простые числа
        return None 
	#Далее рассматривается расширенный алгоритм Евклида
    u1, u2, u3 = 1, 0, a #шаг 1
    v1, v2, v3 = 0, 1, m #шаг 2

    while v3 != 0: #шаг3 пока не 
        q = u3 // v3
        v1, v2, v3, u1, u2, u3 = (u1 - q * v1), (u2 - q * v2), (u3 - q * v3), v1, v2, v3
    return u1 % m



#Здесь проверяем правильность введенного ключа
def check_keys(keyA, keyB, alphabet, mode)-> None:
	if mode == 'encrypt' and keyA == 1 or keyB == 0: sys.exit("Ключ слаб для шифрования. Выберите другой ключ")
	#if mode == 'encrypt'  and : sys.exit('Ключ слаб для шифрования. Выберите другой ключ') 
	if keyA < 0 or keyB < 0 or keyB > len(alphabet) - 1: 
	      sys.exit("Первая часть ключа должна быть >0 и вторая часть ключа должна быть от 0 до {(len(alphabet)-1)}")
	if gcd(keyB, len(alphabet)) != 1: 
		  sys.exit('Первая часть ключа и число символов в алфавите не взаимно простые.Выбрать другой ключ')		
	else: print("Проверка пройдена")

#Т.к. ключ один разделим его на две части
def divide_key(key):
	keyA = key//len(alphabet)
	keyB = key%len(alphabet) 
	return (keyA,keyB)


#Афинный шифр
#Зашифруем сообщение
def affin_encrypt(input_str:str, key:int)->str:
    alphabet = "абвгдеёжзийклмнопрстуфхцчшщъьыэюя"
    encrypted_message = ''#инициализация строки для сообщения
    keyA, keyB = divide_key(key) #выполним разделение нашего ключа на две части
    check_keys(keyA, keyB, alphabet,'encrypt') #проверим ключ
    for char in input_str:
       if char not in alphabet:
          encrypted_message += char #символа нет в алфавите, добавим незашифрованным
       else:
            index = alphabet.find(char)
            encrypted_message += alphabet[(index*keyB + keyA) % len(alphabet)]	#Добавим закодированный символ в сообщение
    return encrypted_message

#Расшифруем сообщение
def affin_decrypt(input_str:str, key:int)->str:
    alphabet = "абвгдеёжзийклмнопрстуфхцчшщъьыэюя"	
    decrypted_message = '' #инициализация строки для сообщения 
    keyA, keyB = divide_key(key) #выполним разделение нашего ключа на две части
    check_keys(keyA, keyB, alphabet, 'decrypt') #проверим ключ
    inverse_keyB = findModInverse(keyB, len(alphabet)) #получим мультипликативную инверсию первой части ключа

    for char in input_str:
        if char not in alphabet:
            decrypted_message += char
        else:
            index = alphabet.find(char)
			#Добавим закодированный символ 
            decrypted_message += alphabet[( index - keyA)*inverse_keyB % len(alphabet)]

    return decrypted_message

def char_frequancy(txt:str)->None:
   b = {}
   mess_len = 0
   #with open('test2.txt',"r") as f:
   for l in txt:
        if (l in alphabet):
                mess_len +=1
                if (l in b):
                    b[l] +=1
                else:
                    b[l] = 1
   #for u in b.keys():
   print('В тексте длиной: {} Частота встречаемоти сообщения {} '.format(mess_len, b.items()))
   #for u in b.keys():
   # print('Символ {} встречается с частотой {: .1f} '.format(u,(b[u]/mess_len)))







#main
print("Начало выполнения программы")
while True:
    mess = input("Сообщение:  ")
    cypher_method = int(input("Введите номер метода шифрования:  "))
    if cypher_method == 1:
       print("\t\vШифр Цезаря:")
       key = int(input("Ключ: "))
       result = cesar_encrypt(mess,key)
       print("Ваше зашифрованное сообщение:  {}".format(result))
       char_frequancy(result)
       result = cesar_decrypt(result,key)
       #print("Ваше исходное сообщение:  {}".format(result))
       #break
    elif cypher_method == 2:
       print("\t\vАфинный шифр")
       key = int(input("Ключ:  "))
       result = affin_encrypt(mess,key) #тест на key = 1334 проходит хорошо
       print("Ваше зашифрованное сообщение:  {}".format(result))
       char_frequancy(result)
       result = affin_decrypt(result,key)
       print("Ваше исходное сообщение:  {}".format(result))
       #break
    elif cypher_method == 3:
       print("\t\v Шифр Плейфера:")
       key_phrase = input("Ключевая фраза:  ")
       result = playfair_encrypt(mess,key_phrase)
       print("Ваше зашифрованое сообщение:  {}".format(result))
       result = playfair_decode(result, key_phrase)
       print("Ваше исходное сообщение:  {}".format(result))

    else: break

#end main
