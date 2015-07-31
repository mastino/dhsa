#include "keygroup.h"

void KeyGroup::setGroupKey(unsigned char *newGroupKey){
  groupKey = newGroupKey;
}

void KeyGroup::cycleGroupKey(){
  getSha256Digest(groupKey);
}
