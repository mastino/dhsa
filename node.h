#include "keygroup.h"

class Node{
private:
  int nodeId;
  KeyGroup kg;
public:
  Node(int id);
  int getNodeId();
  KeyGroup getKeyGroup();
};
