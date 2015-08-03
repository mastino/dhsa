#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

void getSha256Digest(unsigned char *inputDigest);
string printDigest(unsigned char digest[]);
