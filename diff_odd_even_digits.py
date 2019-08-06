#!/bin/env python3

## Finds difference between even and odd digits of a number
def diff_odd_even_digits(num):
    sum = 0
    odd_even_flag = False
    while (num > 0):
        if (odd_even_flag):
            sum += num%10
        else:
            sum -= num%10
        num /= 10
        odd_even_flag ^= True

    return (abs(sum))

## Main program begins here
if __name__ == "__main__":
    num = int(input('Enter a num: '))
    print ('Difference is : ' + str(diff_odd_even_digits(num)))
