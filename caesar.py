def decrypt(coordinates, key=3):
    for num in coordinates:
        p = (num-key) % 26
        print(p, end=' ')
    print('\n')


coordinates1 = [17, 0, 34]
coordinates2 = [68, 2, 48]

for i in range(1, 26):
    print(f'[+] Key number: {i}')
    decrypt(coordinates1, i)
    decrypt(coordinates2, i)
