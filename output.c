#include "output.h"

#include <assert.h>

static unsigned int nextOutput = 1;

unsigned int allocateOutput(void) {
   assert(nextOutput != 0);
   return nextOutput++;
}
