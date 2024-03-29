#!/usr/bin/env python3

'''
Reads a stream of binary input and convert them into readable message

eg: 
01010100 01101000 01100101 00100000 01101100 01100101 01100110 01110100 00100000 01100001 01101110 01100100 00100000 01110100 01101000 01100101 00100000 01110010 01101001 01100111 01101000 01110100 00101110 00100000 01010100 01110111 01101111 00100000 01100011 01101000 01100101 01100101 01101011 01110011 00100000 01101111 01101110 00100000 01110100 01101000 01100101 00100000 01110011 01100001 01101101 01100101 00100000 01100010 01110101 01110100 01110100 00101110 00001010 00001010 01011111 01011111 01011111 01011111 01011111 01011111 01011111 01011111 00001010 00001010 01010111 01001111 01010010 01001100 01000100 01010111 01001001 01000100 01000101 00100000 01010000 01001111 01001100 01001001 01010100 01010010 01001001 01000011 01001011 01010011

o/p:


The left and the right. Two cheeks on the same butt.

________

WORLDWIDE POLITRICKS

'''

def binary_to_txt(line):
    output = []
    words = line.split(' ');
    for word in words:
        num = 0
        for bits in word:
            if (bits == '1'):
                num = (num << 1) | 0x1
            elif (bits == '0'):
                num = (num << 1)
            else:
                num = 0
                break
        output.append(chr(num)) 
    return (''.join(output))
        
if __name__=='__main__':
    input_line = input()
    print ('\n\n' + binary_to_txt(input_line) + '\n')
