#include "onewayhash.h"

class KeyGroup{
private:
  unsigned char *groupKey;
public:
  void setGroupKey(unsigned char *newGroupKey);
  void cycleGroupKey();
}
