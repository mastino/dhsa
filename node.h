
#ifndef NODE_H
#define NODE_H

#include "keygroup.h"
#include "dhmanager.h"
//#include "tree_table.h"


class Node{
private:
  int nodeId;
//  int treeId;
//  EVP_PKEY *paramKey;
//  EVP_PKEY *pKey;
  KeyGroup kg;
//  Table tree_table;
public:
  Node(int id);
//  Node(int id, EVP_PKEY *newParamKey);
  int getNodeId();
  void setGroupKey(unsigned char* newKey);
//  void setParamKey(EVP_PKEY *newParamKey);
  unsigned char* getGroupKey();
  void cycleGroupKey();
  void joinGroup(Node requestedNode);
  void deriveSharedKey(int id);
};


#endif
