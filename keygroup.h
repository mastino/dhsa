#include "onewayhash.h"

class KeyGroup{
public:
  unsigned char *groupKey;
  
  void cycleGroupKey();
};
