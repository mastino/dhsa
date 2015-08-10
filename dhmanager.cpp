#include "dhmanager.h"

DHManager::DHManager(EVP_PKEY *paramKey){
  pKey = NULL;
  peerKey= NULL;
  keyControl = EVP_PKEY_CTX_new(paramKey, NULL);
  EVP_PKEY_keygen_init(keyControl);
}

void DHManager::generateKey(){
  EVP_PKEY_keygen(keyControl, &pKey);
}

EVP_PKEY *DHManager::getKey(){
  return pKey;
}

void DHManager::deriveSharedKey(EVP_PKEY *peer){
  peerKey=peer;
  peerControl = EVP_PKEY_CTX_new(pKey, NULL);
  EVP_PKEY_derive_init(peerControl);
  EVP_PKEY_derive_set_peer(peerControl, peerKey);
  EVP_PKEY_derive(peerControl, NULL, &sharedKeyLength);
  sharedKey = (unsigned char *) OPENSSL_malloc(sharedKeyLength);
  EVP_PKEY_derive(peerControl, sharedKey, &sharedKeyLength);
}
unsigned char* DHManager::getSharedKey(){
  return sharedKey;
}
