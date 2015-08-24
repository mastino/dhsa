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

  virtual bool isLeaf(){}  

  virtual TreeNode* getParentNode(){}
  virtual TreeNode* getLeftChild(){}
  virtual TreeNode* getRightChild(){}
  virtual int getID(){}
  virtual string getBinCode(){}
  virtual string getDecCode(){}
  virtual unsigned char* getKey(){}

  virtual void setKey(unsigned char* new_key){}
  virtual void setBinCode(string new_bin){}
  virtual void setDecCode(string new_dec){}
  virtual void setParentNode(TreeNode* new_parent){}
  virtual void setLeftChild(TreeNode* new_l_child){}
  virtual void setRightChild(TreeNode* new_r_child){}


};

#endif
