#include "onewayhash.h"
#include "tree_table.h"

class KeyGroup{
private:  
  unsigned char *groupKey;
  Node *root_node;
  int leaf_count;
public:
  void KeyGroup();
  void ~KeyGroup();
  void cycleGroupKey();
  void setGroupKey(unsigned char *newKey);
  int setRootNode(Node* new_root_node);
  int addLeafNode(Node* new_leaf);
  unsigned char* getGroupKey();
};
