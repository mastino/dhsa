/* 
 * leaf_node.cpp
 * implementation for tree leaves
*/


#include "leaf_node.h"

using namespace std;

LeafNode::LeafNode() {
  id = -1;
  public_key = EVP_PKEY_new();
  parent_node = NULL;
}


LeafNode::LeafNode(int new_id) {
  id = new_id;
  public_key = EVP_PKEY_new();
  parent_node = NULL;
}

LeafNode::LeafNode(int new_id, EVP_PKEY* new_key, TreeNode* parent) {
  id = new_id;
  public_key = new_key;
  parent_node = parent;
}

LeafNode::~LeafNode() {
  EVP_PKEY_free(public_key);
}
 
int LeafNode::getID() {
  return id;
}

EVP_PKEY* LeafNode::getPublicKey() {
  return public_key;
}


TreeNode* LeafNode::getParentNode() {
  return parent_node;
}

TreeNode* LeafNode::getLeftChild() {
  return NULL;
} 

TreeNode* LeafNode::getRightChild() {
  return NULL;
}

bool LeafNode::isLeaf() {
  return true;
}

// leaves don't have bin codes
string LeafNode::getBinCode() {
  return "X";
}

void LeafNode::setID(int new_id) {
  id = new_id;
}

void LeafNode::setPublicKey(EVP_PKEY* new_pkey) {
  public_key = new_pkey;
}

//pre new_parent is allocated so it won't be deleted accidentally
void LeafNode::setParentNode(TreeNode *new_parent) {
  parent_node = new_parent;
}


