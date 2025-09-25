#include "output.h"

#include <assert.h>

/* remember the next output ID to provide */
static unsigned int nextOutput = 1;

/*
 Give the next available output ID to a requestor.  Output IDs are used by
 writers when writing to a signal to ensure that the same output continues to
 write to the same signal, and to make sure that a signal is always written by
 the same output.
 */
unsigned int allocateOutput(void) {
   assert(nextOutput != 0);
   return nextOutput++;
}
