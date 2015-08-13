/* 
 * middle_node.h
 * header for intermediate tree nodes
*/


#ifndef MIDDLE_NODE
#define MIDDLE_NODE

#include "tree_node.h"

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
  string getBinCode();
  string getDecCode();
  // return true unless root
  TreeNode* getParentNode();
  // return true if child exists
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


};

#endif
