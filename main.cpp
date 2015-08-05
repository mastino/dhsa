#include <stdio.h>
#include <iostream>
#include <openssl/rand.h>
#include "network.h"
#include "aes.h"
#include "dhmanager.h"

using namespace std;

int main(int argc, char** argv){
  // Testing Network class
  Network net = Network(9);
  // Testing Node class
  cout <<  "The id of the node is: " << net.netNodes[0].getNodeId() << endl;

  // Testing the genration of random keys and SHA1 one way hash
  unsigned char key[32];
  RAND_bytes(key, sizeof(key));
  cout << "The original random key is: " << printDigest(key) << endl;
  getSha256Digest(key);
  cout << "The new key is: " << printDigest(key) << endl;

  //Testing KeyGroup class
  unsigned char node1Key[32];
  copy(key, key+32, node1Key);
  net.netNodes[0].setGroupKey(key);
  cout << "The key for node " << net.netNodes[0].getNodeId() << " is: ";
  cout << printDigest(net.netNodes[0].getGroupKey()) << endl;
 
  net.netNodes[1].setGroupKey(node1Key);
  cout << "The key for node " << net.netNodes[1].getNodeId() << " is: ";
  cout << printDigest(net.netNodes[1].getGroupKey()) << endl;

  net.netNodes[0].cycleGroupKey();
  cout << "The key for node " << net.netNodes[0].getNodeId() << " after one way hash is: ";
  cout << printDigest(net.netNodes[0].getGroupKey()) << endl;

  net.netNodes[1].cycleGroupKey();
  cout << "The key for node " << net.netNodes[1].getNodeId() << " after one way hash is: ";
  cout << printDigest(net.netNodes[1].getGroupKey()) << endl;
  
  // Testing AES encryption/decryption
  unsigned char iv[16];
  unsigned char *plaintext = (unsigned char *) "This is a secret";
  unsigned char ciphertext[128];
  unsigned char decrypted[128];
  int dec_len, ciph_len;

  RAND_bytes(iv, sizeof(iv));
  ERR_load_crypto_strings();
  OpenSSL_add_all_algorithms();
  OPENSSL_config(NULL);

  ciph_len = encrypt(plaintext, 16, net.netNodes[0].getGroupKey(), iv, ciphertext);
  
  cout << "Plaintext is: " << plaintext << endl;
  cout << "Ciphertext is:" <<endl;
  BIO_dump_fp(stdout, (const char *) ciphertext, ciph_len);

  dec_len = decrypt(ciphertext, ciph_len, net.netNodes[1].getGroupKey(), iv, decrypted);
  decrypted[dec_len] = '\0';

  cout << "Decrypted text is: " << decrypted << endl;
  
  EVP_cleanup();
  ERR_free_strings();

  // Testing DH class
  DHManager dhm = DHManager();
  
  return 0;
}
