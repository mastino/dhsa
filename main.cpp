#include <iostream>
#include <openssl/rand.h>
#include "onewayhash.h"

using namespace std;

int main(int argc, char** argv){
  unsigned char key[32];
  cout << sizeof(key) <<endl;
  RAND_bytes(key, sizeof(key));
  cout << "The original random key is: " << printDigest(key) << endl;
  getSha256Digest(key);
  cout << "The new key is: " << printDigest(key) << endl;
  return 0;
}
