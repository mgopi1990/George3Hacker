#!/usr/bin/env python3

'''
reverses the input string consisting of numbers,
and store return their relavent char coresponding to ascii
'''
def decode (encoded_text):
    temp_text= encoded_text[::-1]
    temp_string = ''
    decoded_text = ''
    for text in temp_text:
        temp_string += text
        temp_num = int(temp_string)
        if (((temp_num >= 65) and (temp_num <= 90)) or 
            ((temp_num >=97) and (temp_num <= 122)) or 
            (temp_num == 32)):
            decoded_text += chr(temp_num)
            temp_string = ''
    return decoded_text

if __name__ == '__main__':
    #encoded_text = '23511011501782351112179911801562340161171141148'
    encoded_text = '7010117928411101701997927'
    decoded_text = decode(encoded_text)
    print (decoded_text)


