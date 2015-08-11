#include <stdio.h>
#include <iostream>
#include <openssl/rand.h>
#include "network.h"
#include "aes.h"
#include "tree_table.h"

using namespace std;

int main(int argc, char** argv){
  EVP_PKEY *paramKey = NULL;
  EVP_PKEY_CTX *paramControl = EVP_PKEY_CTX_new_id(EVP_PKEY_DH, NULL);
  EVP_PKEY_paramgen_init(paramControl);
  EVP_PKEY_CTX_set_dh_paramgen_prime_len(paramControl, 1024);
  EVP_PKEY_paramgen(paramControl, &paramKey);

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
  DHManager dhm1 = DHManager(paramKey);
  dhm1.generateKey();

  DHManager dhm2 = DHManager(paramKey);
  dhm2.generateKey();

  dhm1.deriveSharedKey(dhm2.getKey());
  dhm2.deriveSharedKey(dhm1.getKey());

  cout << "The shared Diffie-Hellman secret for DHManager 1: " << printDigest(dhm1.getSharedKey()) << endl;
  cout << "The shared Diffie-Hellman secret for DHManager 2: " << printDigest(dhm2.getSharedKey()) << endl;



  cout << endl << endl;
  cout << "-------------- test tree table -------------" << endl;
  cout << "   making leaf nodes ids 0 and 1; both using respective dhm keys" << endl;
  LeafNode leaf_0;
  LeafNode leaf_1;
  leaf_0.id = 0; leaf_1.id = 1;
  leaf_0.public_key = dhm1.getKey();
  leaf_1.public_key = dhm2.getKey();  


  cout << "   leaf 0 id = " << leaf_0.id << endl;

  cout << "   redoing DH test with leaf node param" << endl << endl;

  dhm1.deriveSharedKey(leaf_1.public_key);
  dhm2.deriveSharedKey(leaf_0.public_key);

  cout << "   The shared Diffie-Hellman secret for DHManager 1: " << printDigest(dhm1.getSharedKey()) << endl;
  cout << "   The shared Diffie-Hellman secret for DHManager 2: " << printDigest(dhm2.getSharedKey()) << endl;
  cout << endl;

  cout << "   making leaf pair" << endl;
  LeafPair entry;
  entry.push_back(leaf_0);
  entry.push_back(leaf_1);
  cout << "   leaf pair item 0: " << entry[0].id << endl;
  cout << "   leaf pair item 1:" << entry[1].id << endl;
  cout << endl;

  cout << "   making table size 1" << endl;
  Table credenza;
  credenza.insert(pair<string, LeafPair>("0", entry) );
  cout << "   table spot 0 entry 1 id:" << (credenza.find("0")->second)[1].id << endl;

  
  
  cout << endl << "Goodbye." << endl << endl;
  return 0;
}



















