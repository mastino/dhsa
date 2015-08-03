#include "onewayhash.h"

class KeyGroup{
private:
  unsigned char *groupKey;
public:
  KeyGroup(){ groupKey = new unsigned char[32];};
  void setGroupKey(unsigned char *newGroupKey);
  void cycleGroupKey();
  unsigned char* getGroupKey();
};
