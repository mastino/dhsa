#include <vector>
#include "node.h"

class Network{
private:
  std::vector<Node> netNodes;
public:
  Network(int numNodes);
  std::vector<Node> getNodes();
};
