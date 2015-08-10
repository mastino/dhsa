#include <openssl/evp.h>
#include <openssl/dh.h>

class DHManager{
private:
  EVP_PKEY_CTX *keyControl;
  EVP_PKEY_CTX *paramControl;
  EVP_PKEY_CTX *peerControl;
  EVP_PKEY *peerKey;
  EVP_PKEY *pKey;
  EVP_PKEY *paramKey;
  unsigned char *sharedKey;
  size_t sharedKeyLength;
public:
  DHManager(EVP_PKEY *paramKey);
  void generateKey();
  void deriveSharedKey(EVP_PKEY *peer);
  EVP_PKEY *getKey();
  unsigned char* getSharedKey();
  void setSharedKey(EVP_PKEY *key);
};
