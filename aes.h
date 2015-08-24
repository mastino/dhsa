#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#ifndef AES
#define AES

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext);

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext);

void handleErrors();

#endif
