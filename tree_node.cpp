/*
 * tree_node.cpp
 * parent class for MiddleNode and LeafNode
 * used to build tree
*/

#include "tree_node.h"

using namespace std;

TreeNode::TreeNode() {
  parent_node = NULL; 
}

TreeNode::~TreeNode() {
  //recursi through children?
}

