#include "keygroup.h"

void KeyGroup::KeyGroup() {
  root_node = new Node;
  root_node->middle_node.bin_code = "0";
  root_node->middle_node.dec_code = "0";
  root_node->middle_node.parent_node = NULL;
}

void KeyGroup::~KeyGroup() {
  //recusively delete nodes
}

void KeyGroup::cycleGroupKey(){
  getSha256Digest(groupKey);
}

void KeyGroup::setGroupKey(unsigned char *newKey){
  groupKey = newKey;
  
}

//copies data from new_root_node to root node
//pre new_root_node is middle node with key and children
//post root_node assigned data in new_root_node, bin_code and dec_ccode are "-"
//returns 0 for failure 1 for success
int KeGroup::setRootNode(Node* new_root_node) {
  
  if(new_root_node->middle_node == NULL)
    return 0;
  
  root_node->middle_node.key = new_root_node->middle_node.key; 
  root_node->middle_node.left_child = new_root_node->middle_node.left_child;
  root_node->middle_node.right_child = new_root_node->middle_node.right_child;
  root_node->middle_node.bin_code = "0";
  root_node->middle_node.dec_code = "0";
  
  return 1;

}

int KeGroup::addLeafNode(Node* new_leaf) {

  if(new_leaf->leaf_node == NULL)
    return 0;

  // find spot
  
  // update keys

  // add node
  
}

unsigned char* KeyGroup::getGroupKey(){
  return groupKey;
}
