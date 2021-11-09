# Finds the Greatest Common Divisor of two numbers
import sys


def gcd(num1, num2):

    num1 = abs(int(num1))
    num2 = abs(int(num2))

    if num1 == 0:
        return num2
    if num2 == 0:
        return num1
    if num1 > num2:
        return gcd(num2, num1)
    else:
        return gcd(num1, num2 % num1)


print(gcd(sys.argv[1], sys.argv[2]))
