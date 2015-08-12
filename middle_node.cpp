/* 
 * middle_node.cpp
 * implementation for intermediate tree nodes
*/

#include "middle_node.h"

using namespace std;

MiddleNode::MiddleNode() {
  right_child = left_child = NULL;
}

MiddleNode::MiddleNode(string new_bin, string new_dec, TreeNode* parent, TreeNode* left, TreeNode* right) {
  bin_code = new_bin;
  dec_code = new_dec;
  parent_node = parent;
  left_child = left;
  right_child = right;
}

MiddleNode::~MiddleNode() {

}

void MiddleNode::getKey(unsigned char* key_copy) {
  int i = 0;

  while(key[i] != '\0') {
    key_copy[i] = key[i];
    i++;
  }
}

string MiddleNode::getBinCode() {
  return bin_code;
}

string MiddleNode::getDecCode() {
  return dec_code;
}

// return true unless root
bool MiddleNode::getParentNode(TreeNode* parent) {
  parent = parent_node;
  return !(parent_node == NULL);
}

// return true if child exists
bool MiddleNode::getLeftChild(TreeNode* left) {
  left = left_child;
  return !(left_child == NULL);
}

bool MiddleNode::getRightChild(TreeNode* right) {
  right = right_child;
  return !(right_child == NULL);
}

bool MiddleNode::isLeaf() {
  return false;
}

void MiddleNode::setKey(unsigned char* new_key) {
  int i = 0;

  while(new_key[i] != '\0') {
    key[i] = new_key[i];
    i++;
  }
}

void MiddleNode::setBinCode(string new_bin) {
  bin_code = new_bin;
}

void MiddleNode::setDecCode(string new_dec){
  dec_code = new_dec;
}

void MiddleNode::setParentNode(TreeNode* new_parent) {
  parent_node = new_parent;
}

void MiddleNode::setLeftChild(TreeNode* new_l_child) {
  left_child = new_l_child;
}

void MiddleNode::setRightChild(TreeNode* new_r_child) {
  right_child = new_r_child;
}




