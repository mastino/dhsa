#include "onewayhash.h"
#include "tree_node.h"
#include "leaf_node.h"
#include "middle_node.h"

class KeyGroup{
private:  
  unsigned char *groupKey;
  TreeNode *root_node;
  int leaf_count;
  
  TreeNode* findReplyingNode();

public:
  KeyGroup();
  ~KeyGroup();
  void cycleGroupKey();
  void setGroupKey(unsigned char *newKey);
  int setRootNode(TreeNode* new_root_node);
  unsigned char* getGroupKey();
  int addLeafNode(TreeNode* new_leaf);
};
