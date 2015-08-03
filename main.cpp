#include <stdio.h>
#include <iostream>
#include <openssl/rand.h>
#include "network.h"

using namespace std;

int main(int argc, char** argv){
  // Testing Network class
  Network net = Network(9);
  // Testing Node class
  cout <<  "The id of the node is: " << net.netNodes[0].nodeId << endl;

  // Testing the genration of random keys and SHA1 one way hash
  unsigned char key[32];
  RAND_bytes(key, sizeof(key));
  cout << "The original random key is: " << printDigest(key) << endl;
  getSha256Digest(key);
  cout << "The new key is: " << printDigest(key) << endl;

  //Testing KeyGroup class
  unsigned char node1Key[32];
  copy(key, key+32, node1Key);
  net.netNodes[0].kg.groupKey = key;
  cout << "The key for node " << net.netNodes[0].nodeId << " is: ";
  cout << printDigest(net.netNodes[0].kg.groupKey) << endl;
 
  net.netNodes[1].kg.groupKey = node1Key;
  cout << "The key for node " << net.netNodes[1].nodeId << " is: ";
  cout << printDigest(net.netNodes[1].kg.groupKey) << endl;

  net.netNodes[0].kg.cycleGroupKey();
  cout << "The key for node " << net.netNodes[0].nodeId << " after one way hash is: ";
  cout << printDigest(net.netNodes[0].kg.groupKey) << endl;

  net.netNodes[1].kg.cycleGroupKey();
  cout << "The key for node " << net.netNodes[1].nodeId << " after one way hash is: ";
  cout << printDigest(net.netNodes[1].kg.groupKey) << endl;


  return 0;
}
