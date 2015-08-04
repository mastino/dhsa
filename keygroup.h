#include "onewayhash.h"

class KeyGroup{
private:  
  unsigned char *groupKey;
public:
  void cycleGroupKey();
  void setGroupKey(unsigned char *newKey);
  unsigned char* getGroupKey();
};
