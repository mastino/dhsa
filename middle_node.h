/* 
 * middle_node.h
 * header for intermediate tree nodes
*/


#ifndef MIDDLE_NODE
#define MIDDLE_NODE

#include "tree_node.h"
#include "onewayhash.h"

#define KEY_LEN 32

using namespace std;

class MiddleNode : public TreeNode {

private:
  unsigned char* key;
  string bin_code, dec_code;
  TreeNode *left_child, *right_child;
public:
  MiddleNode();
  MiddleNode(string new_bin, string new_dec, TreeNode *parent, TreeNode *left, TreeNode *right);
  ~MiddleNode();

  unsigned char* getKey();
  void copyKey(unsigned char* copy_key);
  string getBinCode();
  string getDecCode();
  TreeNode* getParentNode();
  TreeNode* getLeftChild();
  TreeNode* getRightChild();

  bool isLeaf();
  int getID();

  void setKey(unsigned char* new_key);
  void setBinCode(string new_bin);
  void setDecCode(string new_dec);
  void setParentNode(TreeNode* new_parent);
  void setLeftChild(TreeNode* new_l_child);
  void setRightChild(TreeNode* new_r_child);

  void renewKey(unsigned char* group_key, int key_length);

};

#endif
