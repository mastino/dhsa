#include <stdio.h>
#include <iostream>
#include <openssl/rand.h>
#include "network.h"
#include "aes.h"
#include "tree_table.h"
#include "tree_node.h"
#include "leaf_node.h"
#include "middle_node.h"
#include <string>


using namespace std;

int main(int argc, char** argv){
  EVP_PKEY *paramKey = NULL;
  EVP_PKEY_CTX *paramControl = EVP_PKEY_CTX_new_id(EVP_PKEY_DH, NULL);
  EVP_PKEY_paramgen_init(paramControl);
  EVP_PKEY_CTX_set_dh_paramgen_prime_len(paramControl, 1024);
  EVP_PKEY_paramgen(paramControl, &paramKey);

  // Testing Network class
  Network net = Network(9, paramKey);
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

  // Testing DH class
  net.netNodes[0].dhm.generateKey();
  net.netNodes[1].dhm.generateKey();

  net.netNodes[0].dhm.deriveSharedKey(net.netNodes[1].dhm.getKey());
  net.netNodes[1].dhm.deriveSharedKey(net.netNodes[0].dhm.getKey());

  cout << "The shared Diffie-Hellman secret for DHManager 0: " << printDigest(net.netNodes[0].dhm.getSharedKey()) << endl;
  cout << "The shared Diffie-Hellman secret for DHManager 1: " << printDigest(net.netNodes[1].dhm.getSharedKey()) << endl;
  
  unsigned char ciphertextDH[128];
  unsigned char decryptedDH[128];
  int dec_len_dh, ciph_len_dh;
  
  ciph_len_dh = encrypt(net.netNodes[0].getGroupKey(), 32, net.netNodes[0].dhm.getSharedKey(), iv, ciphertextDH);

  dec_len_dh = decrypt(ciphertextDH, ciph_len_dh, net.netNodes[1].dhm.getSharedKey(), iv, decryptedDH);
  decrypted[dec_len] = '\0';


  cout << "Group key encrypted by Node 0 with shared DH key: " << endl;
  BIO_dump_fp(stdout, (const char *) ciphertextDH, ciph_len_dh);
  
  cout  << "Group key decrypted by Node 1 with shared DH key: ";
  cout << printDigest(decryptedDH) << endl; 

  EVP_cleanup();
  ERR_free_strings();

  cout << endl << endl;
  cout << "-------------- test tree nodes -------------" << endl;

  cout << "leaf node:"  << endl;
  LeafNode* leaf_0 = new LeafNode();
  leaf_0->setID(0);
  cout << "  leaf id: " << leaf_0->getID() << endl;
  cout << "  leaf 0 is a leaf? ";
  if (leaf_0->isLeaf()) cout << "yes" << endl;
  else cout << "no" << endl;
  
  cout << "middle node:"  << endl;
  MiddleNode* middle_0 = new MiddleNode();
  middle_0->setKey((unsigned char*)"ABCDEFGHIJK");
  unsigned char* print_key;
  middle_0->getKey(print_key);
  cout << "  middle 0 key: " << print_key << endl;
  cout << "  middle 0 is a leaf? ";
  if (leaf_0->isLeaf()) cout << "yes" << endl;
  else cout << "no" << endl;


  cout << endl << "Goodbye." << endl << endl;
  
  return 0;
}
