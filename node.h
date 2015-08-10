
#ifndef NODE_H
#define NODE_H

#include "keygroup.h"
#include "dhmanager.h"
//#include "tree_table.h"


class Node{
private:
  int nodeId;
  KeyGroup kg;
  //Table tree_table;
public:
  Node(int id);
  int getNodeId();
  void setGroupKey(unsigned char* newKey);
  unsigned char* getGroupKey();
  void cycleGroupKey();
  void joinGroup(Node requestedNode);
  void deriveSharedKey(int id);
};


#endif
