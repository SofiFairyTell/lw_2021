import string
import sys
import itertools
import re
# имя файла
FILENAME = "..\\TIPIS\esperanto_full.txt"
FILENAME2 = "..\\TIPIS\m.txt"

# определяем пустой список
messages = list()
 
##for i in range(4):
##    message = input("Введите строку " + str(i+1) + ": ")
##    messages.append(message + "\n")
## 
### запись списка в файл
##with open(FILENAME, "a") as file:
##    for message in messages:
##        file.write(message)
 
### считываем сообщения из файла
##print("Считанные сообщения")
##with open(FILENAME, "r") as file:
##    for message in file:
##        print(message, end="")
symb = [',','.',' ',]
#list = ['b', 'a', 'c', 'd','e','f',' ','l','m','n','h','i','j','k','t','r','w','u']
with open(FILENAME, "r") as file:
    with open(FILENAME2,"a") as file2:
        line = file.readline()
        while line:
            mess = line.lower()
            message = mess.translate({ord(x): '' for x in symb})
            #message = line.replace("f","")
            file2.write(message)
            print(message, end="")
            line = file.readline()
