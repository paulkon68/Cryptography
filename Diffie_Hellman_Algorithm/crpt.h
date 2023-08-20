#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int check_prime(unsigned long long int n){
    unsigned long long int i;
    int flag=0;
    // 0 and 1 are not prime numbers
  // change flag to 1 for non-prime number
  if (n == 0 || n == 1)
    flag = 1;

  for (i = 2; i <= sqrt(n); ++i) {

    // if n is divisible by i, then n is not prime
    // change flag to 1 for non-prime number
    if (n % i == 0) {
      flag = 1;
      break;
    }
  }

  // flag is 0 for prime numbers
  if (flag == 0)
    return 1;
  else
    return 0;
}

// this function generates a big prime number, that is less than q
void generate_prime_number(mpz_t *prime, unsigned long long int q){
    
    char str1[100]; // array to store the random number (helps with conversion)
    int test;
    unsigned long long int rn;

    rn = rand()%RAND_MAX;  // generate a random number

    while(rn > q || check_prime((rn-1)/2)|| rn < 50) rn = rand()%RAND_MAX;  // if rn > q, generate new random number
    sprintf(str1, "%lld", rn);  // convert the rn number and store it to char array str1
    mpz_init_set_str(*prime, str1, 10);  // initialize the value pointed by prime to the number stored in str1

    test = mpz_probab_prime_p(*prime, 20);  // if *prime object contains a prime number, test will be equal to 2

    // check if prime variable contains a prime 
    while(1){
        if(test != 2){  // if test is not a prime number
            rn = rand()%RAND_MAX;  // generate a new random number
            while(rn >= q || check_prime((rn-1)/2) || rn < 500){  // while rn > q, generate a new random number
                rn = rand()%RAND_MAX;
            }
            sprintf(str1, "%lld", rn);
            mpz_init_set_str(*prime, str1, 10);
            test = mpz_probab_prime_p(*prime, 20);
        }
        else{  // else we have a big prime number so end the loop
            break;
        }
    }
}

// this function creates a substitution array for the substitution cipher of size: length
unsigned int *create_substitution_array(int length){

    unsigned int *substitution_array = (unsigned int *)malloc(sizeof(unsigned int)*length);
    size_t i;
    size_t row;
    size_t possible_position;
    
    // initialize all array values to zero
    for(i = 0; i < length; i++){
        substitution_array[i] = 0;
    }
    
    // each element of index i of the substitution_array, will now contain a value from 0-length
    // For example: substitution_array[2] = 12, means that the 2nd character of a message should be 
    // placed in position 12 for the substitution cipher
    for(i = 0; i < length; i++){

        do{
            row = rand() % length;
        } while (substitution_array[row] != 0);
        substitution_array[row] = i;
    }
    return substitution_array;
}

void *encrypt(unsigned char *message, int length, unsigned char *cipher, unsigned int *sub_array, unsigned char salt){
    
    size_t i;  // initialize the counter

    // create the substituion cipher
    for(i = 0; i < length; i++){
        cipher[sub_array[i]] = message[i]; 
    }

    // XOR all characters of cipher array with the value of the variable salt
    for(i = 0; i < length; i++){
        cipher[i] = salt ^ cipher[i]; 
    }
    cipher[i] = '\0';
}

void *decrypt(unsigned char *cipher, int length, unsigned char *message, unsigned int *sub_array, unsigned char salt){

    size_t i;  // initialize the counter

    // reverse XOR encryption on every character of cipher
    for(i = 0; i < length; i++){
        cipher[i] = salt ^ cipher[i];
    }

    // reverse substitution of the characters of the message based on the substitution array
    for(i = 0; i < length; i++){
        message[i] = cipher[sub_array[i]];
    }
    message[i] = '\0';
}
