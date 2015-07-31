#include <iostream>
#include <openssl/rand.h>
#include "onewayhash.h"
#include "node.h"

using namespace std;

int main(int argc, char** argv){
  // Testing Node class
  Node n1 = Node(1);
  cout <<  "The id of the node is: " << n1.getNodeId() << endl;

  // Testing the genration of random keys and SHA1 one way hash
  unsigned char key[32];
  RAND_bytes(key, sizeof(key));
  cout << "The original random key is: " << printDigest(key) << endl;
  getSha256Digest(key);
  cout << "The new key is: " << printDigest(key) << endl;
  return 0;
}
