#ifndef NODE_H
#define NODE_H

#include "keygroup.h"
#include "dhmanager.h"

class Node{
private:
  int nodeId;
  KeyGroup kg;
public:
  DHManager dhm = NULL;
  Node(int id, EVP_PKEY *params);
  int getNodeId();
  void setGroupKey(unsigned char* newKey);
  unsigned char* getGroupKey();
  void cycleGroupKey();
  void joinGroup(Node requestedNode);
  void deriveSharedKey(int id);
};
#endif
