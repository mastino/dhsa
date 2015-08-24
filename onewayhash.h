#ifndef ONE_WAY_HASH
#define ONE_WAY_HASH

#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

void getSha256Digest(unsigned char *inputDigest);
string printDigest(unsigned char digest[]);

#endif
