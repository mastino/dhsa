#include "keygroup.h"
#include <queue>

using namespace std;

void KeyGroup::KeyGroup() {
  root_node = new TreeNode;
  root_node->leaf_node = NULL;
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

unsigned char* KeyGroup::getGroupKey(){
  return groupKey;
}

//copies data from new_root_node to root node
//pre new_root_node is middle node with key and children
//post root_node assigned data in new_root_node, bin_code and dec_ccode are "-"
//returns 0 for failure 1 for success
int KeGroup::setRootNode(TreeNode* new_root_node) {
  
  if(new_root_node->middle_node == NULL)
    return 0;
  
  root_node->leaf_node = NULL;
  root_node->middle_node.key = new_root_node->middle_node.key; 
  root_node->middle_node.left_child = new_root_node->middle_node.left_child;
  root_node->middle_node.right_child = new_root_node->middle_node.right_child;
  root_node->middle_node.bin_code = "0";
  root_node->middle_node.dec_code = "0";
  
  return 1;

}

//adds new leaf to the tree
//pre public key and id are defined
//post parent node is assigned to new leaf
//     new keys are created as necessary
int KeGroup::addLeafNode(TreeNode* new_leaf) {

  if(new_leaf->leaf_node == NULL)
    return 0;


  // find spot for new tree node
  TreeNode* replying_node = findReplyingNode();  
  TreeNode* new_middle = new TreeNode;
  new_middle->leaf_node = NULL;
  new_middle->middle_node = new MiddleNode;
  new_middle->middle_node.key = //TODO
  new_middle->middle_node.bin_code = //TODO
  new_middle->middle_node.dec_code = //TODO
  new_middle->middle_node.parent_node = replying_node->leaf_node.parent_node;
  new_middle->middle_node.right_child = 
  new_middle->middle_node.left_child = 


  
  // update keys

  // add node
  
} //End addLeafNode

//locates next place to insert a leaf
//returns the new leaf's soon-to-be sibling
//  if NULL returned there was an error
TreeNode* KeyGroup::findReplyingNode() {

  TreeNode* tracking_node = NULL;
  TreeNode* replying_node = NULL;
  queue <TreeNode*> search_queue;
  bool left_is_leaf, right_is_leaf;

  search_queue.push(root_node);
  while( (replying_node == NULL) && (!search_queue.empty()) ) {
    
    tracking_node = search_queue.front();
    search_queue.pop();    

    left_is_leaf  = (tracking_node->left_child->leaf_node  != NULL);
    right_is_leaf = (tracking_node->right_child->leaf_node != NULL);

    if( left_is_leaf && right_is_leaf )
       replying_node = tracking_node->left_child;
    else if( left_is_leaf && !right_is_leaf )
       replying_node = tracking_node->left_child;
    else if( !left_is_leaf && right_is_leaf )
       replying_node = tracking_node->right_child;
    else if( !left_is_leaf && !right_is_leaf ){
       search_queue.push(tracking_node->left_child);
       search_queue.push(tracking_node->right_child);
    }

  }

  return replying_node;

} //End findReplyingNode






