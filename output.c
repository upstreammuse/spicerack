#include "output.h"

int nextOutput = 1000;

/* TODO fail when wrapping around? */
int allocateOutput(void) {
   return nextOutput++;
}
