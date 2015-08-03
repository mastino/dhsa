#include "onewayhash.h"

void getSha256Digest(unsigned char *inputDigest){
  SHA256_CTX shaControl;
  SHA256_Init(&shaControl);
  SHA256_Update(&shaControl, inputDigest, 256);
  SHA256_Final(inputDigest, &shaControl);
}

string printDigest(unsigned char digest[]){
  stringstream ss;
  for(int i=0; i<SHA256_DIGEST_LENGTH; i++){
    ss << hex << setw(2) << setfill('0') << (int)digest[i];
  }
  return ss.str();
}

