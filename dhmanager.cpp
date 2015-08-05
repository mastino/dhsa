#include "dhmanager.h"

DHManager::DHManager(){
  paramKey = NULL;
  privateKey = NULL;
  paramControl = EVP_PKEY_CTX_new_id(EVP_PKEY_DH, NULL);
  EVP_PKEY_paramgen_init(paramControl);
  EVP_PKEY_CTX_set_dh_paramgen_prime_len(paramControl, 1024);
  EVP_PKEY_paramgen(paramControl, &paramKey);
  keyControl = EVP_PKEY_CTX_new(paramKey, NULL);
  EVP_PKEY_keygen_init(keyControl);
}

void DHManager::generateKey(){
  EVP_PKEY_keygen(keyControl, &privateKey);
}
