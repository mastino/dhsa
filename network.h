
#ifndef NETWROK_H
#define NETWORK_H

#include <vector>
#include "node.h"

class Network{
public:
  std::vector<Node> netNodes;

  Network(int numNodes);
};

#endif
