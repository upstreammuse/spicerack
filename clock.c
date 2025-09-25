#include "clock.h"

#include "output.h"
#include "signal.h"

#include <assert.h>
#include <stdlib.h>

static void clockRunTick(struct Clock* clock, enum SignalValue value);

struct SignalNode {
   struct Signal* item;
   struct SignalNode* next;
};

struct Clock {
   int OID;
   struct SignalNode* inputs;
};

struct Clock* clockNew(void) {
   struct Clock* clock = malloc(sizeof (struct Clock));
   clock->inputs = NULL;
   clock->OID = allocateOutput();
   return clock;
}

void clockFree(struct Clock* clock) {
   if (clock == NULL) return;
   while (clock->inputs != NULL) {
      struct SignalNode* node = clock->inputs;
      clock->inputs = node->next;
      free(node);
   }
   free(clock);
}

void clockConnect(struct Clock* clock, struct Signal* line) {
   struct SignalNode* node = malloc(sizeof (struct SignalNode));
   assert(clock != NULL);
   assert(line != NULL);
   node->item = line;
   node->next = clock->inputs;
   clock->inputs = node;
}

void clockRun(struct Clock* clock, unsigned int cycleCount) {
   assert(clock != NULL);
   if (cycleCount == 0) {
      while (1) {
         clockRunTick(clock, HIGH);
         clockRunTick(clock, LOW);
      }
   } else {
      unsigned int i;
      for (i = 0; i < cycleCount; i++) {
         clockRunTick(clock, HIGH);
         clockRunTick(clock, LOW);
      }
   }
}

static void clockRunTick(struct Clock* clock, enum SignalValue value) {
   SignalList* node;
   assert(clock != NULL);
   for (node = clock->inputs; node != NULL; node = node->next) {
      signalWrite(node->item, value, clock->OID);
   }
   signalPropagate();
}
