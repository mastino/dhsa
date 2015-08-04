#include "keygroup.h"

void KeyGroup::cycleGroupKey(){
  getSha256Digest(groupKey);
}

void KeyGroup::setGroupKey(unsigned char *newKey){
  groupKey = newKey;
}

unsigned char* KeyGroup::getGroupKey(){
  return groupKey;
}
