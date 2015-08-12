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

// return true unless root
bool LeafNode::getParentNode(TreeNode* parent) {
  parent = parent_node;
  return !(parent_node == NULL);
}

// return false and point to null
bool LeafNode::getLeftChild(TreeNode* left) {
  left = NULL;
  return false;
} 

// point to null and return false
bool LeafNode::getRightChild(TreeNode* right) {
  right = NULL;
  return false;
}

bool LeafNode::isLeaf() {
  return true;
}

void LeafNode::setID(int new_id) {
  id = new_id;
}

void LeafNode::setPublicKey(EVP_PKEY* new_pkey) {
  public_key = new_pkey;
}

//pre new_parent is allocated so it won't be deleted accidentally
void LeafNode::setParentNode(TreeNode* new_parent) {
  parent_node = new_parent;
}


