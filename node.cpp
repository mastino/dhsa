#include "node.h"

Node::Node(int id){
  nodeId = id;  
}

int Node::getNodeId(){
  return nodeId;
}

void Node::setGroupKey(unsigned char* newKey){
  kg.setGroupKey(newKey);
}

unsigned char* Node::getGroupKey(){
  return kg.getGroupKey();
}

void Node::cycleGroupKey(){
  kg.cycleGroupKey();
}
void Node::deriveSharedKey(int nodeToDerive){

}

void Node::joinGroup(Node requestedNode){
  
}
