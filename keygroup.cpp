#include "keygroup.h"

void KeyGroup::cycleGroupKey(){
  getSha256Digest(groupKey);
}
