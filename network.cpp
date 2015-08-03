#include "network.h"

Network::Network(int numNodes){
  for(int i = 0; i < numNodes; ++i){
    netNodes.push_back(Node(i));
  }
}
std::vector<Node> Network::getNodes(){
  return netNodes;
}
