import sys
import math
 
def main():
    entropy()

def entropy():
    print('Opening file {}...'.format(sys.argv[1]))
    with open(sys.argv[1], 'rb') as f:
        byteArr = list(f.read())
    fileSize = len(byteArr)
    print
    print('Размер файла в байтах: {:,d}'.format(fileSize))
    # calculate the frequency of each byte value in the file
    print('Вычисляю реальную энтропию...')
    freqList = []
    for b in range(256):
        ctr = 0
        for byte in byteArr:
            if byte == b:
                ctr += 1
        freqList.append(float(ctr) / fileSize)
    # Shannon entropy
    ent = 0.0
    for freq in freqList:
        if freq > 0:
            ent = ent + freq * math.log(freq, 2)
    ent = -ent
    print('Реальная энтропия: {}'.format(ent))
    print
 
if __name__== "__main__":
    main()
