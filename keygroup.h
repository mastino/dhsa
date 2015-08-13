#include "onewayhash.h"
#include "tree_node.h"
#include "leaf_node.h"
#include "middle_node.h"

class KeyGroup{
private:  
  unsigned char *groupKey;
  MiddleNode* root_node;
  int leaf_count;
  
  TreeNode* findReplyingNode(bool& right_branch);

public:
  KeyGroup();
  ~KeyGroup();
  void cycleGroupKey();
  void setGroupKey(unsigned char *newKey);
  int setRootNode(MiddleNode* new_root_node);
  unsigned char* getGroupKey();
  int addLeafNode(LeafNode* new_leaf);
};
