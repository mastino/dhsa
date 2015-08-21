
#include "keygroup.h"

KeyGroup::KeyGroup() {
  root_node = new MiddleNode("0", "0", NULL, NULL, NULL);
}

KeyGroup::~KeyGroup() {
  //recusively delete nodes
}

void KeyGroup::cycleGroupKey(){
  //getSha256Digest(groupKey);
  root_node->setKey(groupKey);

  MiddleNode* tracking_node = NULL;
  queue <MiddleNode*> travel_queue;
  bool left_is_leaf, right_is_leaf;

  travel_queue.push(root_node);
  while( !travel_queue.empty() ) {

    tracking_node = travel_queue.front();
    tracking_node->renewKey(groupKey, KEY_LEN);
    
    if ((tracking_node->getLeftChild()) != NULL)
      left_is_leaf  = (tracking_node->getLeftChild())->isLeaf();
    else
      left_is_leaf = true; //prevents attempts to use left child

    if ((tracking_node->getRightChild()) != NULL)  
      right_is_leaf = (tracking_node->getRightChild())->isLeaf();
    else
      right_is_leaf = true; //prevents attempts to use right child

    if( !left_is_leaf ){
      travel_queue.push((MiddleNode*)(tracking_node->getLeftChild()));
    } 
    if( !right_is_leaf ) {
      travel_queue.push((MiddleNode*)(tracking_node->getRightChild()));
    }

    travel_queue.pop();
  }

  root_node->copyKey(groupKey);
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
int KeyGroup::addLeafNode(LeafNode* new_leaf, LeafNode* reply_node, bool right_branch) {

  if( !(new_leaf->isLeaf()) )
    return 0;
  if( reply_node->isLeaf() )
    return 0;

  // generate new codes
  cycleGroupKey();
  string new_dec = reply_node->getParentNode()->getDecCode();
  string new_bin = reply_node->getParentNode()->getBinCode();
  if (right_branch) new_bin.append("1");
  else new_bin.append("0");   
  string new_digit( 1, (char)(rand() % 10) + 0x30 );
  new_dec.append( new_digit );

  //update keys
  cycleGroupKey();

  MiddleNode* new_middle = new MiddleNode(new_bin, new_dec, reply_node->getParentNode(), reply_node, new_leaf);
  if (right_branch) reply_node->getParentNode()->setRightChild(new_middle);
  else reply_node->getParentNode()->setLeftChild(new_middle);
  new_middle->renewKey(groupKey, KEY_LEN);
  reply_node->setParentNode(new_middle);
  new_leaf->setParentNode(new_middle);

  return 1;  

} //End addLeafNode


//removes leaf node and upddates keys
//pre make new key first
//    new_key is KEN_LEN chars
//returns 1 if success 0 if fail
//TODO parent is root case or tree balancing on leave
int KeyGroup::removeLeafNode(int id, unsigned char* new_key) {

  MiddleNode *parent, *grand_parent;
  LeafNode *leaving_node;
  TreeNode *sibling;
  bool leaving_is_right, parent_is_right;

  leaving_node = (LeafNode*)findLeafNode(id);

  if( !(leaving_node->isLeaf()) )
    return 0;

  parent = (MiddleNode*)(leaving_node->getParentNode());
  grand_parent = (MiddleNode*)(parent->getParentNode());

  if( grand_parent == NULL )
    return 0; //case parent is root, requires major tree reorganization

  leaving_is_right = (parent->getRightChild()->getID() == id);
  parent_is_right = (grand_parent->getRightChild()->getBinCode()).compare(parent->getBinCode()) == 0 ;
  if(leaving_is_right)
    sibling = parent->getLeftChild();
  else 
    sibling = parent->getRightChild();
    
  sibling->setParentNode(grand_parent);
  if(parent_is_right)
    grand_parent->setRightChild(sibling);
  else
    grand_parent->setLeftChild(sibling);

  leaving_node->~LeafNode();
  parent->~MiddleNode();

  setGroupKey(new_key);
  cycleGroupKey();

}

//locates next place to insert a leaf
//returns the new leaf's soon-to-be sibling
//  if NULL returned there was an error
//
// this may be unecessary
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


//locates leaf by id (BFS)
//returns the pointer to leaf
//  if NULL then not found
TreeNode* KeyGroup::findLeafNode(int target_id) {

  TreeNode* tracking_node = NULL;
  TreeNode* target_node = NULL;
  queue <TreeNode*> search_queue;
  int left_id, right_id;

  search_queue.push(root_node);
  while( (target_node == NULL) && (!search_queue.empty()) ) {

    tracking_node = search_queue.front();
    search_queue.pop();

    left_id  = (tracking_node->getLeftChild())->getID();
    right_id = (tracking_node->getRightChild())->getID();

    if( left_id = target_id ) {
       target_node = tracking_node->getLeftChild();
    } else if( right_id = target_id ) {
       target_node = tracking_node->getRightChild();
    } 

    if( left_id == -1 ) {
       search_queue.push(tracking_node->getLeftChild());
    } 
    if( right_id == -1 ){
       search_queue.push(tracking_node->getRightChild());
    }

  }

  return target_node;

} //End findLeavingNode




