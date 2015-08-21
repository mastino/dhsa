/* 
 * middle_node.cpp
 * implementation for intermediate tree nodes
*/

#include "middle_node.h"

using namespace std;

MiddleNode::MiddleNode() {
  right_child = left_child = NULL;
  key = new unsigned char[KEY_LEN];
}

MiddleNode::MiddleNode(string new_bin, string new_dec, TreeNode *parent, TreeNode *left, TreeNode *right) {
  bin_code = new_bin;
  dec_code = new_dec;
  parent_node = parent;
  left_child = left;
  right_child = right;
  key = new unsigned char[KEY_LEN];
}

//WARNING this may cause memory leak if children aren't deleted
MiddleNode::~MiddleNode() {
  delete key;
  right_child = NULL;
  left_child = NULL;
}

unsigned char* MiddleNode::getKey() {
  return key;
}

//@pre copy key must have KEY_LEN spots
void MiddleNode::copyKey(unsigned char* copy_key) {
  for(int i = 0; i < KEY_LEN; i++) {
     copy_key[i] = key[i];
  }
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

//@pre new key must have KEY_LEN characters
void MiddleNode::setKey(unsigned char* new_key) {
  for(int i = 0; i < KEY_LEN; i++) {
     key[i] = new_key[i];
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

void MiddleNode::renewKey(unsigned char* group_key, int key_length) {
  //Key = f(K_group xor dec_Code)
  int dec_length = dec_code.length();
  unsigned char*  dec_chars = new unsigned char[dec_length + 1];
  dec_chars = (unsigned char*) dec_code.c_str();

  int i;
  for(i = 1; i <= dec_length; i++) {
    key[key_length - i] = group_key[key_length - i] ^ (dec_chars[dec_length - i] - 0x30);
  }
  for(i; i <= key_length; i++) {
    key[key_length - i] = group_key[key_length - i]; //remaining bytes are oxr'ed with 0
  }
  getSha256Digest(key);
}


