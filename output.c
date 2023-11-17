#include "output.h"

#include <assert.h>

unsigned int nextOutput = 1;

unsigned int allocateOutput(void) {
   assert(nextOutput != 0);
   return nextOutput++;
}
