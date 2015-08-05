#include <openssl/evp.h>
#include <openssl/dh.h>

class DHManager{
private:
  EVP_PKEY_CTX *keyControl;
  EVP_PKEY_CTX *paramControl;
  EVP_PKEY *privateKey;
  EVP_PKEY *paramKey;
public:
  DHManager();
  void generateKey();
};
