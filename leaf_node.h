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
  // return true unless root
  bool getParentNode(TreeNode* parent);
  // return false and point to null
  bool getLeftChild(TreeNode* left);
  bool getRightChild(TreeNode* right);

  bool isLeaf();  

  void setID(int new_id);
  void setPublicKey(EVP_PKEY* new_pkey);
  void setParentNode(TreeNode* new_parent);

};

#endif
