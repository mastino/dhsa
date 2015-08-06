#include "dhmanager.h"

DHManager::DHManager(EVP_PKEY &paramKey){
  pKey = NULL;
  keyControl = EVP_PKEY_CTX_new(paramKey, NULL);
  EVP_PKEY_keygen_init(keyControl);
}

void DHManager::generateKey(){
  EVP_PKEY_keygen(keyControl, &pKey);
}

EVP_PKEY DHManager::getKey(){
  return *pKey;
}

void DHManager::derive(int id){
}

unsigned char* DHManager::getSharedKey(int id){
  return sharedKeys[id];
}
