/* 
 * leaf_node.h
 * header for tree leaves
*/


#ifndef LEAF_NODE
#define LEAF_NODE

#include "tree_node.h"

using namespace std;

class LeafNode : public TreeNode {

private:
  int id;
  EVP_PKEY *public_key;
public:
  LeafNode();
  LeafNode(int new_id);
  LeafNode(int new_id, EVP_PKEY* new_key, TreeNode* parent);
  ~LeafNode();
 
  int getID();
  EVP_PKEY* getPublicKey();
  TreeNode* getParentNode();
  TreeNode* getLeftChild();
  TreeNode* getRightChild();
  string getDecCode();
  string getBinCode();

  bool isLeaf();

  void setID(int new_id);
  void setPublicKey(EVP_PKEY* new_pkey);
  void setParentNode(TreeNode* new_parent);
 
  virtual void setKey(unsigned char* new_key){}
  virtual void setBinCode(string new_bin){}
  virtual void setDecCode(string new_dec){}
  virtual void setLeftChild(TreeNode* new_l_child){}
  virtual void setRightChild(TreeNode* new_r_child){}


};

#endif
