#include "network.h"

Network::Network(int numNodes, EVP_PKEY *params){
  for(int i = 0; i < numNodes; ++i){
    netNodes.push_back(Node(i, params));
  }
}
