#include <openssl/evp.h>
#include <openssl/dh.h>
#include <openssl/bio.h>
#include <map>

class DHManager{
private:
  EVP_PKEY_CTX *keyControl;
  EVP_PKEY_CTX *paramControl;
  EVP_PKEY *pKey;
  EVP_PKEY *paramKey;
  std::map <int, unsigned char *> sharedKeys;
public:
  DHManager(EVP_PKEY &paramKey);
  void generateKey();
  void derive(int id);
  EVP_PKEY getKey();
  unsigned char* getSharedKey(int id);
  void setSharedKey(EVP_PKEY *key);
};
