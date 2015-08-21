#include "onewayhash.h"
#include "tree_node.h"
#include "leaf_node.h"
#include "middle_node.h"
#include <stdlib.h>
#include <string>
#include <queue>

using namespace std;

#define KEY_LEN 32  //bytes

class KeyGroup{
private:  
  unsigned char *groupKey;
  MiddleNode* root_node;
  int leaf_count;
  
public:
  KeyGroup();
  ~KeyGroup();
  void cycleGroupKey();
  void setGroupKey(unsigned char *newKey);
  int setRootNode(MiddleNode* new_root_node);
  void startTree(unsigned char* new_key, LeafNode* left_leaf, LeafNode* right_leaf);
  unsigned char* getGroupKey();
  int addLeafNode(LeafNode* new_leaf, LeafNode* reply_node, bool right_branch);
  int removeLeafNode(int id, unsigned char* new_key);
  TreeNode* findReplyingNode(bool& right_branch);
  TreeNode* findLeafNode(int target_id);

};
