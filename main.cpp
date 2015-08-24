#include <stdio.h>
#include <iostream>
#include <openssl/rand.h>
#include "network.h"
#include "aes.h"
#include "tree_table.h"
#include "tree_node.h"
#include "leaf_node.h"
#include "middle_node.h"
#include "dhmanager.h"
#include "keygroup.h"
#include <string>


using namespace std;

void basicTest();
void testTreeNodes();
void buildTreeTest();

int main(int argc, char** argv){
 
  cout << endl << endl;
  cout << "                  Testing DHSA" << endl;
  cout << "-----------------------------------------------" << endl << endl;
  
  buildTreeTest();  

  cout << endl << endl;
  cout << "-----------------------------------------------" << endl;
  cout << "                   Goodbye :) ";
  cout << endl << endl << endl;

  return 0;

}

void basicTest() { 

  EVP_PKEY *paramKey = NULL;
  EVP_PKEY_CTX *paramControl = EVP_PKEY_CTX_new_id(EVP_PKEY_DH, NULL);
  EVP_PKEY_paramgen_init(paramControl);
  EVP_PKEY_CTX_set_dh_paramgen_prime_len(paramControl, 1024);
  EVP_PKEY_paramgen(paramControl, &paramKey);

  cout << endl << "----- Testing Network and Node constructors -----" << endl <<endl;
  // Testing Network class
  Network net = Network(9, paramKey);
  // Testing Node class
  cout <<  "The id of the node is: " << net.netNodes[0].getNodeId() << endl;

  // Testing the genration of random keys and SHA1 one way hash
  cout << endl << "----- Testing Random 256 bit key generation and SHA-1 function -----" << endl << endl;

  unsigned char key[32];
  RAND_bytes(key, sizeof(key));
  cout << "The original random key is: " << printDigest(key) << endl << endl;
  getSha256Digest(key);
  cout << "The new key is: " << printDigest(key) << endl;

  //Testing KeyGroup class
  cout << endl << "----- Testing Key Group -----" << endl << endl;
  unsigned char node1Key[32];
  copy(key, key+32, node1Key);
  net.netNodes[0].setGroupKey(key);
  cout << "The key for node " << net.netNodes[0].getNodeId() << " is: ";
  cout << printDigest(net.netNodes[0].getGroupKey()) << endl << endl;
 
  net.netNodes[1].setGroupKey(node1Key);
  cout << "The key for node " << net.netNodes[1].getNodeId() << " is: ";
  cout << printDigest(net.netNodes[1].getGroupKey()) << endl <<endl;

  net.netNodes[0].cycleGroupKey();
  cout << "The key for node " << net.netNodes[0].getNodeId() << " after one way hash is: ";
  cout << printDigest(net.netNodes[0].getGroupKey()) << endl << endl;

  net.netNodes[1].cycleGroupKey();
  cout << "The key for node " << net.netNodes[1].getNodeId() << " after one way hash is: ";
  cout << printDigest(net.netNodes[1].getGroupKey()) << endl;
  
  // Testing AES encryption/decryption
  cout << endl << "----- Testing AES Encryption/Decryption -----" << endl << endl;
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
  
  cout << "Plaintext is: " << plaintext << endl <<endl;
  cout << "Ciphertext is:" <<endl;
  BIO_dump_fp(stdout, (const char *) ciphertext, ciph_len);

  dec_len = decrypt(ciphertext, ciph_len, net.netNodes[1].getGroupKey(), iv, decrypted);
  decrypted[dec_len] = '\0';

  cout << endl << "Decrypted text is: " << decrypted << endl;

  // Testing DH class
  cout << endl << "----- DH Parameters/Key Generation/Key Exchange -----" << endl << endl;
  net.netNodes[0].dhm.generateKey();
  net.netNodes[1].dhm.generateKey();

  net.netNodes[0].dhm.deriveSharedKey(net.netNodes[1].dhm.getKey());
  net.netNodes[1].dhm.deriveSharedKey(net.netNodes[0].dhm.getKey());

  cout << "The shared Diffie-Hellman secret for DHManager 0: " << printDigest(net.netNodes[0].dhm.getSharedKey()) << endl << endl;
  cout << "The shared Diffie-Hellman secret for DHManager 1: " << printDigest(net.netNodes[1].dhm.getSharedKey()) << endl <<endl;
  
  unsigned char ciphertextDH[128];
  unsigned char decryptedDH[128];
  int dec_len_dh, ciph_len_dh;
  
  ciph_len_dh = encrypt(net.netNodes[0].getGroupKey(), 32, net.netNodes[0].dhm.getSharedKey(), iv, ciphertextDH);

  dec_len_dh = decrypt(ciphertextDH, ciph_len_dh, net.netNodes[1].dhm.getSharedKey(), iv, decryptedDH);
  decrypted[dec_len] = '\0';


  cout << "Group key encrypted by Node 0 with shared DH key: " << endl << endl;
  BIO_dump_fp(stdout, (const char *) ciphertextDH, ciph_len_dh);
  
  cout << endl << "Group key decrypted by Node 1 with shared DH key: ";
  cout << printDigest(decryptedDH) << endl; 

  EVP_cleanup();
  ERR_free_strings();
 
}


void testTreeNodes() {

  cout << endl << endl;
  cout << "-------------- test tree nodes -------------" << endl;

  cout << "leaf node:"  << endl;
  LeafNode leaf_0;
  leaf_0.setID(0);
  cout << "  leaf 0 id: " << leaf_0.getID() << endl;
  LeafNode leaf_1; leaf_1.setID(1);
  cout << "  leaf 1 id: " << leaf_1.getID() << endl;
  LeafNode leaf_2; leaf_2.setID(2);
  cout << "  leaf 2 id: " << leaf_2.getID() << endl;
  cout << "  leaf 0 is a leaf? ";
  if (leaf_0.isLeaf()) cout << "yes" << endl;
  else cout << "no" << endl;
  cout << endl;  
  cout << "middle node:"  << endl;
  MiddleNode middle_0;
  unsigned char* fake_key = (unsigned char*) "ABCDEFGHIJK";
  middle_0.setKey(fake_key);
  cout << "  middle 0 key: " << middle_0.getKey() << endl;
  cout << "  middle 0 is a leaf? ";
  if (middle_0.isLeaf()) cout << "yes" << endl;
  else cout << "no" << endl;
  middle_0.setBinCode("01");
  cout << "  middle 0 bin code: " << middle_0.getBinCode() << endl;
  cout << "  (should be '01')"  << endl;
  middle_0.setDecCode("04");
  cout << "  middle 0 dec code: " << middle_0.getDecCode() << endl;
  cout << "  (should be '04')"  << endl;
  cout << endl;
  cout << "tree node:" << endl;
  cout << "  making tree..." << endl;
  MiddleNode root_node = MiddleNode("0", "0", NULL, &middle_0, &leaf_0);
  middle_0.setParentNode(&root_node);
  leaf_0.setParentNode(&root_node);
  cout << "  root node bin code: " << root_node.getBinCode() << endl;
  cout << "  (should be '0')"  << endl;
  middle_0.setLeftChild(&leaf_1);
  leaf_1.setParentNode(&middle_0);
  middle_0.setRightChild(&leaf_2);
  leaf_2.setParentNode(&middle_0);
  cout << "  middle 0 left child ID: " << middle_0.getLeftChild()->getID() << endl;
  cout << "  (should be 1)" << endl;
  cout << "  traversing..." << endl;
  TreeNode *traveller = new TreeNode();
  traveller = &root_node;
  if (traveller->getLeftChild() != NULL) {
    traveller = traveller->getLeftChild();
    cout << "    went left" << endl;
    cout << "    traversal at ID: " << traveller->getID() << endl;
    cout << "            BinCode: " << traveller->getBinCode() << endl;
  } else {
    cout << "    oops!" << endl;
  }
  if (traveller->getRightChild() != NULL) {
    traveller = traveller->getRightChild();
    cout << "    went right" << endl;
    cout << "    traversal at ID: " << traveller->getID() << endl;
    cout << "            BinCode: " << traveller->getBinCode() << endl;
  } else {
    cout << "    oops!" << endl;
  }
  if (traveller->getParentNode() != NULL) {
    traveller = traveller->getParentNode();
    cout << "    went up" << endl;
    cout << "    traversal at ID: " << traveller->getID() << endl;
    cout << "            BinCode: " << traveller->getBinCode() << endl;
  } else {
    cout << "    oops!" << endl;
  }
  if (traveller->getParentNode() != NULL) {
    traveller = traveller->getParentNode();
    cout << "    went up" << endl;
    cout << "    traversal at ID: " << traveller->getID() << endl;
    cout << "            BinCode: " << traveller->getBinCode() << endl;
  } else {
    cout << "    oops!" << endl;
  }
  if (traveller->getParentNode() != NULL) {
    traveller = traveller->getParentNode();
    cout << "    went up" << endl;
    cout << "    traversal at ID: " << traveller->getID() << endl;
    cout << "            BinCode: " << traveller->getBinCode() << endl;
  } else {
    cout << "    oops!" << endl;
  }

}

void buildTreeTest() {
  
  cout << endl << "----- Testing KeyGroup Joining and Leaving -----" << endl <<endl;

  int numLeaves = 6;
  int next_leaf = 0;

  KeyGroup myGroup;
  LeafNode* leaves[numLeaves];

  EVP_PKEY *paramKey = NULL;
  EVP_PKEY_CTX *paramControl = EVP_PKEY_CTX_new_id(EVP_PKEY_DH, NULL);
  EVP_PKEY_paramgen_init(paramControl);
  EVP_PKEY_CTX_set_dh_paramgen_prime_len(paramControl, 1024);
  EVP_PKEY_paramgen(paramControl, &paramKey);

  DHManager dhManager(paramKey);
  dhManager.generateKey();
  EVP_PKEY *fillerKey = dhManager.getKey();;

  //do not implement network this way
  //all DH key are the same; this is not secure
  //just filling storage for testing
  for(int i = 0; i < 6; i++)
    leaves[i] = new LeafNode(i, fillerKey, NULL);

  unsigned char key[32];
  RAND_bytes(key, sizeof(key));
  unsigned char newKey[32];
  RAND_bytes(newKey, sizeof(newKey));
  getSha256Digest(newKey);

  cout << "-- starting KeyGroup" << endl;
  myGroup.startTree(key, leaves[next_leaf], leaves[next_leaf + 1]);
  next_leaf += 2;
  cout << "   The group key is:  " << printDigest(myGroup.getGroupKey()) << endl;
  cout << "   The leaf count is: " << myGroup.getLeafCount() << endl;
  cout << "   Left Leaf ID is:   " << (myGroup.getRootNode())->getLeftChild()->getID() << endl;
  cout << "   Right Leaf ID is:  " << (myGroup.getRootNode())->getRightChild()->getID() << endl;


  cout << "-- adding Leaf: " << leaves[next_leaf]->getID() << endl;
  bool is_right;
  LeafNode* temp = (LeafNode*) myGroup.findReplyingNode(is_right);
  if ( temp == NULL )
     cout << "ERROR finding reply" << endl;
  cout << "   replying node id:   " << temp->getID() << endl;
  if ( myGroup.addLeafNode(leaves[next_leaf], temp, is_right) == 0)
     cout << "ERROR adding" << endl;
  cout << "   The group key is:  " << printDigest(myGroup.getGroupKey()) << endl;
  cout << "   The middle key is: " << printDigest(temp->getParentNode()->getKey()) << endl;
  cout << "   The leaf count is: " << myGroup.getLeafCount() << endl;
  next_leaf++;

  cout << "-- adding Leaf: " << leaves[next_leaf]->getID() << endl;
  temp = (LeafNode*) myGroup.findReplyingNode(is_right);
  if ( temp == NULL )
     cout << "ERROR finding reply" << endl;
  cout << "   replying node id:   " << temp->getID() << endl;
  if ( myGroup.addLeafNode(leaves[next_leaf], temp, is_right) == 0)
     cout << "ERROR adding" << endl;
  cout << "   The group key is:   " << printDigest(myGroup.getGroupKey()) << endl;
  cout << "   The middle key is: " << printDigest(temp->getParentNode()->getKey()) << endl;
  cout << "   The leaf count is: " << myGroup.getLeafCount() << endl;
  next_leaf++;


  cout << "-- adding Leaf: " << leaves[next_leaf]->getID() << endl;
  temp = (LeafNode*) myGroup.findReplyingNode(is_right);
  if ( temp == NULL )
     cout << "ERROR finding reply" << endl;
  cout << "   replying node id:   " << temp->getID() << endl;
  if ( myGroup.addLeafNode(leaves[next_leaf++], temp, is_right) == 0)
     cout << "ERROR adding" << endl;
  cout << "   The group key is:  " << printDigest(myGroup.getGroupKey()) << endl;
  cout << "   The middle key is: " << printDigest(temp->getParentNode()->getKey()) << endl;
  cout << "   The leaf count is: " << myGroup.getLeafCount() << endl;
  next_leaf++;

  cout << "-- checking bin and dec codes" << endl;
  cout << "   root node bin:  " << (myGroup.getRootNode())->getBinCode() << endl;
  cout << "   root node dec:  " << (myGroup.getRootNode())->getDecCode() << endl;
  cout << "   left node bin:  " << (myGroup.getRootNode())->getLeftChild()->getBinCode() << endl;
  cout << "   left node dec:  " << (myGroup.getRootNode())->getLeftChild()->getDecCode() << endl;
  cout << "   right node bin: " << (myGroup.getRootNode())->getRightChild()->getBinCode() << endl;
  cout << "   right node dec: " << (myGroup.getRootNode())->getRightChild()->getDecCode() << endl;

  cout << endl << endl;

  cout << "-- removing Leaf: 4" << endl;
  if ( myGroup.removeLeafNode(4, newKey) == 0 )
     cout << "ERROR remmoving 4" << endl;
  cout << "   The group key is:  " << printDigest(myGroup.getGroupKey()) << endl;
  cout << "   The leaf count is: " << myGroup.getLeafCount() << endl;




}









