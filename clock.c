#include "clock.h"

#include "spicerack.h"

#include <assert.h>
#include <stdlib.h>

struct InputLineNode {
   struct InputLine* item;
   struct InputLineNode* next;
};

typedef struct InputLineNode NODE;

struct Clock {
   NODE* inputs;
   int OID;
};

CLOCK* clockNew(void) {
   CLOCK* clock = malloc(sizeof (CLOCK));
   clock->inputs = NULL;
   clock->OID = allocateOutput();
   return clock;
}

void clockFree(CLOCK* clock) {
   while (clock->inputs != NULL) {
      NODE* node = clock->inputs;
      clock->inputs = node->next;
      free(node);
   }
   free(clock);
}

void clockConnect(CLOCK* clock, struct InputLine* line) {
   NODE* node = malloc(sizeof (NODE));
   assert(clock != NULL);
   assert(line != NULL);
   node->item = line;
   node->next = clock->inputs;
   clock->inputs = node;
}

void clockRunTick(CLOCK* clock, enum SignalValue value) {
   NODE* node;
   for (node = clock->inputs; node != NULL; node = node->next) {
      inputLineSet(node->item, value, clock->OID);
   }
   propagate();
}

void clockRun(CLOCK* clock, int cycleCount) {
   int i;
   if (cycleCount == -1) {
      while (1) {
         clockRunTick(clock, HIGH);
         clockRunTick(clock, LOW);
      }
   } else {
      for (i = 0; i < cycleCount; i++) {
         clockRunTick(clock, HIGH);
         clockRunTick(clock, LOW);
      }
   }
}
