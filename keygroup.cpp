
#include "keygroup.h"
#include <queue>

using namespace std;

KeyGroup::KeyGroup() {
  root_node = new MiddleNode("0", "0", NULL, NULL, NULL);
}

KeyGroup::~KeyGroup() {
  //recusively delete nodes
}

void KeyGroup::cycleGroupKey(){
  getSha256Digest(groupKey);
  root_node->setKey(groupKey);
}

void KeyGroup::setGroupKey(unsigned char *newKey){
  groupKey = newKey;
  root_node->setKey(groupKey);
}

unsigned char* KeyGroup::getGroupKey(){
  return groupKey;
}

//copies data from new_root_node to root node
//pre new_root_node is middle node with key and children
//post root_node assigned data in new_root_node, bin_code and dec_ccode are "-"
//returns 0 for failure 1 for success
int KeyGroup::setRootNode(MiddleNode* new_root_node) {
  
  if(new_root_node->isLeaf())
    return 0;
  
  root_node = new_root_node;
  root_node->setBinCode("0");
  root_node->setDecCode("0");
  
  return 1;

}

//adds new leaf to the tree
//pre public key and id are defined
//post parent node is assigned to new leaf
//     new keys are created as necessary
int KeyGroup::addLeafNode(LeafNode* new_leaf) {

  if( !(new_leaf->isLeaf()) )
    return 0;


  // find spot for new tree node
  bool right_branch = true;
  LeafNode* replying_node = (LeafNode*)findReplyingNode(right_branch);
  
  //TODO generate new codes
  cycleGroupKey();
  string new_dec = replying_node->getParentNode()->getDecCode();
  string new_bin = replying_node->getParentNode()->getBinCode();
  if (right_branch) new_bin.append("1");
  else new_bin.append("0");   
  

  //TODO update keys

  TreeNode* new_middle = new MiddleNode(new_bin, new_dec, replying_node->getParentNode(), replying_node, new_leaf);
  if (right_branch) replying_node->getParentNode()->setRightChild(new_middle);
  else replying_node->getParentNode()->setLeftChild(new_middle);
  //TODO new_middle->estKey(???);
  replying_node->setParentNode(new_middle);
  new_leaf->setParentNode(new_middle);

  return 1;  

} //End addLeafNode

//locates next place to insert a leaf
//returns the new leaf's soon-to-be sibling
//  if NULL returned there was an error
TreeNode* KeyGroup::findReplyingNode(bool& right_branch) {

  TreeNode* tracking_node = NULL;
  TreeNode* replying_node = NULL;
  queue <TreeNode*> search_queue;
  bool left_is_leaf, right_is_leaf;

  search_queue.push(root_node);
  while( (replying_node == NULL) && (!search_queue.empty()) ) {
    
    tracking_node = search_queue.front();
    search_queue.pop();    

    left_is_leaf  = (tracking_node->getLeftChild())->isLeaf();
    right_is_leaf = (tracking_node->getRightChild())->isLeaf();

    if( left_is_leaf && right_is_leaf ){
       replying_node = tracking_node->getLeftChild();
       right_branch = false;
    } else if( left_is_leaf && !right_is_leaf ) {
       replying_node = tracking_node->getLeftChild();
       right_branch = false;
    } else if( !left_is_leaf && right_is_leaf ) {
       replying_node = tracking_node->getRightChild();
       right_branch = true;
    } else if( !left_is_leaf && !right_is_leaf ){
       search_queue.push(tracking_node->getLeftChild());
       search_queue.push(tracking_node->getRightChild());
    }

  }

  return replying_node;

} //End findReplyingNode






