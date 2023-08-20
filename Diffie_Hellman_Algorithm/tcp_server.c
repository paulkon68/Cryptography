#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include "crpt.h"
#include <gmp.h>
#include <unistd.h> // read(), write(), close()


#define MAX 1000  // maximum number of characters for a message
#define PORT 8080
#define SA struct sockaddr

// defined in "crpt.h"
void generate_prime_number(mpz_t *prime, unsigned long long range);  // generates a big prime number
unsigned int *create_substitution_array(int length);
void *encrypt(unsigned char *message, int length, unsigned char *cipher, unsigned int *sub_array, unsigned char salt);
void *decrypt(unsigned char *cipher, int length, unsigned char *message, unsigned int *sub_array, unsigned char salt);

unsigned long int diffie_hellman_key_exchange(int fd){

    mpz_t q;    // a big prime number
    mpz_t a;    // primitive root of q (usually a = 3)
    mpz_t Xa;   // secret key of Alice
    mpz_t Ya;   // public key of Alice
    mpz_t Yb;  // public key of Bob
    mpz_t shared_key;  // shared key

    char buffer[32];  // temporary buffer for conversions
    unsigned long long int uli_q;
    unsigned long long int uli_a;
    unsigned long long int uli_Yb;
    unsigned long long int uli_Ya;

    // initialization of the mpz_t pointers to structs
    mpz_init(q);
    mpz_init(a);
    mpz_init(Xa);
    mpz_init(Ya);
    mpz_init(Yb);
    mpz_init(shared_key);


    mpz_init_set_str (a, "2", 10);  // a is a primitive root of q, a = 3

    generate_prime_number(&q, RAND_MAX);  // generate a random q (prime)
    uli_q = mpz_get_ui(q);  // convert mpz_t type q, to unsigned long int
    generate_prime_number(&Xa, uli_q);  // generate a random secret key for Alice

    // convert q and a to unsigned long int and sent them to Bob
    uli_q = mpz_get_ui(q);
    uli_a = mpz_get_ui(a);

    write(fd, &uli_q, sizeof(uli_q));  // sent q to Bob
    write(fd, &uli_a, sizeof(uli_a));  // sent a to Bob

    printf("\nPrime number q = %llu (public [sent to Bob])\n", uli_q);
    printf("Primitive root of q, a = %llu (public [sent to Bob])\n", uli_a);
    gmp_printf("Xa = %Zd (private)\n", Xa);
    
    // receive the public key Yb from Bob
    read(fd, &uli_Yb, sizeof(uli_Yb));
    printf("Yb = %llu (sent by Bob)\n", uli_Yb);

    mpz_powm (Ya, a, Xa, q);  // compute the public key of Alice: Ya = a ^ Xa (mod q)
    uli_Ya = mpz_get_ui(Ya);

    printf("Ya = %llu\n", uli_Ya); 
    write(fd, &uli_Ya, sizeof(uli_Ya));  // sent the public key of Alice, Ya to Bob

    sprintf(buffer, "%llu", uli_Yb);   // convert unsigned long int to char array
    mpz_init_set_str(Yb, buffer, 10);  

    mpz_powm (shared_key, Yb, Xa, q);  // compute the shared key: Yb^Xa (mod q)
    gmp_printf("Shared Key = %Zd\n", shared_key);

    return mpz_get_ui(shared_key);  // return the shared key as unsigned long int type
}

// Function for chatting between client and server.
void func(int connfd, unsigned long long int key)
{
    // arrays used to store the messages 
    unsigned char buff[MAX];
    unsigned char mes[MAX];
    int message_length;
    int n;  // used as a counter
    int *sub_array;  // pointer to the substitution array
    unsigned char salt;

    srand((unsigned int)key);  // initialize the pseudo-random number generator
    // infinite loop for chat
    for (;;) {
        
        // clear the buff array
        bzero(buff, MAX);
        
        // read the message from client and copy it in buffer
        read(connfd, buff, sizeof(buff));

        // print the encrypted message sent by Bob (client)
        printf("[!] Encrypted Message By Bob: %s\n", buff);

        // decryption process begins
        salt = rand()%255;  // random value 0-255
        message_length = strlen(buff);
        sub_array = create_substitution_array(message_length);
        decrypt(buff, message_length, mes, sub_array, salt);
        
        // print the decrypted message
        puts("[--Decryption Succeeded--]");
        printf("Bob sent: %s\n To Bob : ", mes);
        bzero(buff, MAX);

        n = 0;
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n')
            ;
        
        // encryption of the message to be sent
        salt = rand()%255;  // random value 0-255
        sub_array = create_substitution_array(n-1);
        encrypt(buff, n-1, mes, sub_array, salt);

        // sent the encrypted message
        write(connfd, mes, sizeof(mes));
   
        // if buff contains "exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }

    }
}
   

int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    unsigned long long int key;

    srand(time(NULL));

    // create the socket 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
   
    // Binding newly created socket to given IP
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");
   
    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);
   
    // Accept the data packet from client
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");
    
    // key obtained by the diffie-hellman key exchange algorithm
    key = diffie_hellman_key_exchange(connfd);

    // Function for chatting between client and server
    func(connfd, key);
   
    // close the socket
    close(sockfd);
}
