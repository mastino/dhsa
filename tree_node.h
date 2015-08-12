/* 
 * tree_node.h
 * parent class for MiddleNode and LeafNode
 * used to build tree
*/


#ifndef TREE_NODE
#define TREE_NODE

#include <openssl/evp.h>
#include <openssl/dh.h>
#include <string>

using namespace std;

class TreeNode {

protected:
  TreeNode *parent_node;
public:
  inline TreeNode() { parent_node = NULL; }
  inline TreeNode(TreeNode* parent) { parent_node = parent; }
  ~TreeNode();
  
  //returns false if root otherwise true
  virtual bool getParentNode(TreeNode* parent);
  virtual bool getLeftChild(TreeNode* left);
  virtual bool getRightChild(TreeNode* right);

  virtual bool isLeaf();

};

#endif
