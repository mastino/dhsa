#include <iostream>
#include <openssl/rand.h>
#include "network.h"

using namespace std;

int main(int argc, char** argv){
  // Testing Network class
  Network net = Network(9);
  // Testing Node class
  cout <<  "The id of the node is: " << net.getNodes()[0].getNodeId() << endl;

  // Testing the genration of random keys and SHA1 one way hash
  unsigned char key[32];
  RAND_bytes(key, sizeof(key));
  cout << "The original random key is: " << printDigest(key) << endl;
  getSha256Digest(key);
  cout << "The new key is: " << printDigest(key) << endl;

  //Testing KeyGroup class
  net.getNodes()[0].getKeyGroup().setGroupKey(key);
  cout << "The key for node " << net.getNodes()[0].getNodeId() << " is: ";
  cout << printDigest(net.getNodes()[0].getKeyGroup().getGroupKey()) << endl;
  return 0;
}
