def decrypt(numeric_list, key=3):
    for num in numeric_list:
        p = (num-key) % 26
        print(p, end=' ')
    print('\n')


for i in range(1, 26):
    print(f'[+] Key number: {i}')
    decrypt([1, 2, 3, 4, 5], i)
