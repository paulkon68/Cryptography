#include <arpa/inet.h> // inet_addr()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include "crpt.h"
#include <gmp.h>
#include <strings.h> // bzero()
#include <unistd.h> // read(), write(), close()

#define MAX 1000
#define PORT 8080
#define SA struct sockaddr

// defined in "crpt.h"
void generate_prime_number(mpz_t *prime, unsigned long long int q);  // generates a big prime number
unsigned int *create_substitution_array(int length);
void *encrypt(unsigned char *message, int length, unsigned char *cipher, unsigned int *sub_array, unsigned char salt);
void *decrypt(unsigned char *cipher, int length, unsigned char *message, unsigned int *sub_array, unsigned char salt);

unsigned long int diffie_hellman_key_exchange(int fd){

    mpz_t q;    // a big prime number
    mpz_t a;    // primitive root of q (usually a = 3)
    mpz_t Xb;   // secret key of Bob
    mpz_t Yb;  // public key of Bob
    mpz_t Ya;  // public key of Alice 
    mpz_t shared_key;  // shared key 

    char buffer[32];  // temporary buffer for conversions
    unsigned long long int uli_q;  // unsigned long long int types of the above numeric elements of DH Algorithm
    unsigned long long int uli_a;
    unsigned long long int uli_Yb;
    unsigned long long int uli_Ya;

    // initialization of the mpz_t pointers to structs
    mpz_init(q);
    mpz_init(a); 
    mpz_init(Yb);
    mpz_init(Ya);
    mpz_init(shared_key);

    srand(time(NULL));  // random seed each sec

    read(fd, &uli_q, sizeof(uli_q));  // read the sent prime number q
    read(fd, &uli_a, sizeof(uli_a));  // read the sent primitive root of q, a
    

    printf("\nPrime number q = %llu (public [sent by Alice])\n", uli_q);
    printf("Primitive root of q, a = %llu (public [sent by Alice])\n", uli_a);
    
    sprintf(buffer, "%llu", uli_q);   // convert unsigned long int to char array
    mpz_init_set_str(q, buffer, 10);  // initialize the mpz_t q struct from string buffer

    sprintf(buffer, "%llu", uli_a);   // convert unsigned long int to char array
    mpz_init_set_str(a, buffer, 10);  // initialize the mpz_t a struct from string buffer
    
    // [ publicly available ] q, a numbers are now known to client

    generate_prime_number(&Xb, uli_q);  // generate a random secret key for Bob (not known to Alice)
    gmp_printf("Xb = %Zd (private)\n", Xb);
    mpz_powm (Yb, a, Xb, q);  // compute the public key of Bob: Yb = a ^ Xb (mod q)

    uli_Yb = mpz_get_ui(Yb);
    write(fd, &uli_Yb, sizeof(uli_Yb));  // sent the public key Yb of Bob to Alice 
    printf("Yb = %llu\n", uli_Yb);

    read(fd, &uli_Ya, sizeof(uli_Ya));  // receive the public key Ya of Alice
    printf("Ya = %llu (sent by Alice)\n", uli_Ya);

    sprintf(buffer, "%llu", uli_Ya);   // convert unsigned long int to char array
    mpz_init_set_str(Ya, buffer, 10);  // initialize the mpz_t Ya struct from string buffer 

    mpz_powm (shared_key, Ya, Xb, q);  // compute the shared key: Ya^Xb (mod q)
    gmp_printf("Shared key = %Zd\n", shared_key);


    return mpz_get_ui(shared_key);  // return the shared key as unsigned long int type
}

void func(int sockfd, unsigned long long int key)
{   
    // arrays used to store the messages 
    unsigned char buff[MAX];
    unsigned char mes[MAX];
    int n;  // used as a counter
    int message_length;
    int *sub_array;  // pointer to the substitution array
    unsigned char salt;
    
    srand((unsigned int)key);  // initialize the pseudo-random number generator

    // infinite loop for chat
    for (;;) {
        
        // clear the buff array
        bzero(buff, sizeof(buff));

        printf("Enter the message : ");

        // store the message to the buff array
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        
        // encryption of the message to be sent
        salt = rand()%255;  // random value 0-255
        sub_array = create_substitution_array(n-1);
        encrypt(buff, n-1, mes, sub_array, salt);
        
        write(sockfd, mes, sizeof(mes));  // send the encrypted message to Alice
        
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));  // receive the encrypted message

        // print the encrypted message
        printf("[!] Encrypted Message By Bob: %s\n", buff);

        // decryption process begins
        salt = rand()%255;  // random value 0-255
        message_length = strlen(buff);
        sub_array = create_substitution_array(message_length);
        decrypt(buff, message_length, mes, sub_array, salt);
        
        // print the decrypted message
        puts("[--Decryption Succeeded--]");
        printf("Alice : %s ", mes);

        // if mes contains exit, then end the chat 
        if ((strncmp(mes, "exit", 4)) == 0) {
            printf("Server Disconnected...\n");
            break;
        }

    }
}
 
int main()
{

    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    unsigned long int key;

    // socket create 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
 
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
        != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
    
    // key obtained by the diffie-hellman key exchange algorithm
    key = diffie_hellman_key_exchange(sockfd);

    // function for chatting between client and server
    func(sockfd, key);
 
    // close the socket
    close(sockfd);
}
