#include "onewayhash.h"
#include "tree_table.h"

class KeyGroup{
private:  
  unsigned char *groupKey;
  TreeNode *root_node;
  int leaf_count;
  
  TreeNode* findReplyingNode();

public:
  void KeyGroup();
  void ~KeyGroup();
  void cycleGroupKey();
  void setGroupKey(unsigned char *newKey);
  int setRootNode(TreeNode* new_root_node);
  unsigned char* getGroupKey();
  int addLeafNode(TreNode* new_leaf);
};
