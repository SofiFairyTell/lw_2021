import itertools
import string
import sys

#глобальные переменные
alphabet='абвгдеёжзийклмнопрстуфхцчшщъьыэюя_,.'

def chunker(seq, size):
    it = iter(seq)
    while True:
        chunk = tuple(itertools.islice(it, size))
        if not chunk:
            return
        yield chunk


def prepare_input(dirty: str) -> str:
    """
    Prepare the plaintext by up-casing it
    and separating repeated letters with X's
    """




    dirty = "".join([c.upper() for c in dirty if c in string.ascii_letters])
    clean = ""

    if len(dirty) < 2:
        return dirty

    for i in range(len(dirty) - 1):
        clean += dirty[i]

        if dirty[i] == dirty[i + 1]:
            clean += "X"

    clean += dirty[-1]

    if len(clean) & 1:
        clean += "X"

    return clean


def generate_table(key: str) -> [str]:

    # I and J are used interchangeably to allow
    # us to use a 5x5 table (25 letters)
    alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"
    # we're using a list instead of a '2d' array because it makes the math
    # for setting up the table and doing the actual encoding/decoding simpler
    table = []

    # copy key chars into the table if they are in `alphabet` ignoring duplicates
	#upper - из fff в FFF
    for char in key.upper():
        if char not in table and char in alphabet:
            table.append(char)

    # fill the rest of the table in with the remaining alphabet chars
    for char in alphabet:
        if char not in table:
            table.append(char)

    return table


def encode(plaintext: str, key: str) -> str:
    table = generate_table(key)
    plaintext = prepare_input(plaintext)
    ciphertext = ""

    # https://en.wikipedia.org/wiki/Playfair_cipher#Description
    for char1, char2 in chunker(plaintext, 2):
        row1, col1 = divmod(table.index(char1), 5)
        row2, col2 = divmod(table.index(char2), 5)

        if row1 == row2:
            ciphertext += table[row1 * 5 + (col1 + 1) % 5]
            ciphertext += table[row2 * 5 + (col2 + 1) % 5]
        elif col1 == col2:
            ciphertext += table[((row1 + 1) % 5) * 5 + col1]
            ciphertext += table[((row2 + 1) % 5) * 5 + col2]
        else:  # rectangle
            ciphertext += table[row1 * 5 + col2]
            ciphertext += table[row2 * 5 + col1]

    return ciphertext


def decode(ciphertext: str, key: str) -> str:
    table = generate_table(key)
    plaintext = ""

    # https://en.wikipedia.org/wiki/Playfair_cipher#Description
    for char1, char2 in chunker(ciphertext, 2):
        row1, col1 = divmod(table.index(char1), 5)
        row2, col2 = divmod(table.index(char2), 5)

        if row1 == row2:
            plaintext += table[row1 * 5 + (col1 - 1) % 5]
            plaintext += table[row2 * 5 + (col2 - 1) % 5]
        elif col1 == col2:
            plaintext += table[((row1 - 1) % 5) * 5 + col1]
            plaintext += table[((row2 - 1) % 5) * 5 + col2]
        else:  # rectangle
            plaintext += table[row1 * 5 + col2]
            plaintext += table[row2 * 5 + col1]

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
def findModInverse(a: int, m: int) -> int:
    if gcd(a, m) != 1:#это означает, что a и m не взаимно простые числа
        return None 
	#Далее рассматривается расширенный алгоритм Евклида
    u1, u2, u3 = 1, 0, a #шаг 1
    v1, v2, v3 = 0, 1, m #шаг 2

    while v3 != 0: #шаг3 пока не 
        q = u3 // v3
        t1,t2,t3 = (u1 - q * v1), (u2 - q * v2), (u3 - q * v3) #с вспомгательным вектором
        v1, v2, v3 = u1, u2, u3
        u1, u2, u3 = t1, t2, t3 
       #v1, v2, v3, u1, u2, u3 = (u1 - q * v1), (u2 - q * v2), (u3 - q * v3), v1, v2, v3
    return u1 % m

#Т.к. ключ один разделим его на две части
def divide_key(key):
	keyA = key//len(alphabet)
	keyB = key%len(alphabet)
	return (keyA,keyB)

def check_keys(keyA, keyB, mode):
    if keyA == 1 or keyB == 0  and mode == 'encrypt':
       sys.exit('Ключ слаб для шифрования. Выберите другой ключ')
   

def affin_encrypt(input_str:str, key:int)->str:
	
	keyA, keyB = divide_key(key) #выполним разделение нашего ключа на две части
	encrypted_message = ""

	for char in input_str:
		if char not in alphabet:
			encrypted_message += char
		else:
			index = (alphabet.index(char)*keyA + keyB) % len(alphabet)
			#Добавим закодированный символ 
			encrypted_message += alphabet[index]		

	return encrypted_message

def affin_decrypt(input_str:str, key:int)->str:
	keyA, keyB = divide_key(key) #выполним разделение нашего ключа на две части
	
	for char in input_str:
		if char not in alphabet:
			encrypted_message += char
		else:
			index = (alphabet.index(char)*keyA + keyB) % len(alphabet)
			#Добавим закодированный символ 
			decrypted_message += alphabet[index]

	return decrypted_message

#main
print("Start our program ")
str = input("String and key ")
str = 'chypher'
result = encode(str,'YTR')
print("Ваше зашифрованное сообщение:{}".format(result))
result = decode(result,'YTR')
print("Ваше исходное сообщение:{}".format(result))

str = 'цезарь'
result = cesar_encrypt(str,1)
print("Ваше зашифрованное сообщение:{}".format(result))


count = len(result)
for i in range(count):
	print(i,end=" ")
	
#end main
