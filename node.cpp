#include "node.h"

Node::Node(int id){
  nodeId = id;
}

int Node::getNodeId(){
  return nodeId;
}

KeyGroup Node::getKeyGroup(){
  return kg;
}
