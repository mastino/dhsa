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
  TreeNode();
  ~TreeNode();
  
  //returns false if root otherwise true
  virtual TreeNode* getParentNode(){}
  virtual TreeNode* getLeftChild(){}
  virtual TreeNode* getRightChild(){}

  virtual bool isLeaf(){}
  virtual int getID(){}
  virtual string getBinCode(){}

};

#endif
