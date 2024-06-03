#include "clock.h"

#include "output.h"
#include "signal.h"

#include <assert.h>
#include <stdlib.h>

typedef struct Clock CLOCK;
typedef struct SignalNode NODE;
typedef struct Signal SIGNAL;
typedef enum SignalValue SIGVAL;

static void clockRunTick(CLOCK* clock, SIGVAL value);

struct SignalNode {
   struct Signal* item;
   struct SignalNode* next;
};

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
   if (clock == NULL) return;
   while (clock->inputs != NULL) {
      NODE* node = clock->inputs;
      clock->inputs = node->next;
      free(node);
   }
   free(clock);
}

void clockConnect(CLOCK* clock, SIGNAL* line) {
   NODE* node = malloc(sizeof (NODE));
   assert(clock != NULL);
   assert(line != NULL);
   node->item = line;
   node->next = clock->inputs;
   clock->inputs = node;
}

void clockRun(CLOCK* clock, unsigned int cycleCount) {
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

static void clockRunTick(CLOCK* clock, SIGVAL value) {
   NODE* node;
   assert(clock != NULL);
   for (node = clock->inputs; node != NULL; node = node->next) {
      signalWrite(node->item, value, clock->OID);
   }
   signalPropagate();
}
