#include "clock.h"

#include "output.h"
#include "signal.h"

#include <assert.h>
#include <stdlib.h>

static void clockRunTick(struct Clock* clock, enum SignalValue value);

struct SignalNode {
   struct Signal* signal;
   struct SignalNode* next;
};

struct Clock {
   struct SignalNode* signals;
   unsigned int OID;
};

struct Clock* clockNew(void) {
   struct Clock* clock = malloc(sizeof (struct Clock));
   clock->signals = NULL;
   clock->OID = allocateOutput();
   return clock;
}

void clockFree(struct Clock* clock) {
   if (clock == NULL) return;
   while (clock->signals != NULL) {
      struct SignalNode* node = clock->signals;
      clock->signals = node->next;
      free(node);
   }
   free(clock);
}

void clockConnect(struct Clock* clock, struct Signal* line) {
   struct SignalNode* node = malloc(sizeof (struct SignalNode));
   assert(clock != NULL);
   assert(line != NULL);
   node->signal = line;
   node->next = clock->signals;
   clock->signals = node;
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
   struct SignalNode* node;
   assert(clock != NULL);
   for (node = clock->signals; node != NULL; node = node->next) {
      signalWrite(node->signal, value, clock->OID);
   }
   signalPropagate();
}
