/* 
 * middle_node.cpp
 * implementation for intermediate tree nodes
*/

#include "middle_node.h"

using namespace std;

MiddleNode::MiddleNode() {
  right_child = left_child = NULL;
}

MiddleNode::MiddleNode(string new_bin, string new_dec, TreeNode *parent, TreeNode *left, TreeNode *right) {
  bin_code = new_bin;
  dec_code = new_dec;
  parent_node = parent;
  left_child = left;
  right_child = right;
}

MiddleNode::~MiddleNode() {

}

unsigned char* MiddleNode::getKey() {
  return key;
}

string MiddleNode::getBinCode() {
  return bin_code;
}

string MiddleNode::getDecCode() {
  return dec_code;
}

TreeNode* MiddleNode::getParentNode() {
  return parent_node;
}

TreeNode* MiddleNode::getLeftChild() {
  return left_child;
}

TreeNode* MiddleNode::getRightChild() {
  return right_child;
}

bool MiddleNode::isLeaf() {
  return false;
}

//middle nodes don't have ID
int MiddleNode::getID() {
  return -1;;
}

void MiddleNode::setKey(unsigned char* new_key) {
  key = new_key;
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




