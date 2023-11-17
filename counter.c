#include "counter.h"

#include "output.h"
#include "signal.h"

#include <assert.h>
#include <stdlib.h>

typedef struct Counter COUNTER;
typedef struct Signal SIGNAL;
typedef enum SignalValue SIGVAL;

void counterHandler(void* block);

struct Counter {
   SIGNAL* clk;
   SIGNAL* rst;
   int next;
   SIGNAL* out[4];
   int outID[4];
};

COUNTER* counterNew(void) {
   COUNTER* c = malloc(sizeof (COUNTER));
   c->clk = signalNew(c, counterHandler);
   c->rst = signalNew(c, counterHandler);
   c->next = -1;
   c->out[0] = NULL;
   c->out[1] = NULL;
   c->out[2] = NULL;
   c->out[3] = NULL;
   c->outID[0] = allocateOutput();
   c->outID[1] = allocateOutput();
   c->outID[2] = allocateOutput();
   c->outID[3] = allocateOutput();
   return c;
}

void counterFree(COUNTER* counter) {
   if (counter == NULL) return;
   signalFree(counter->clk);
   signalFree(counter->rst);
   free(counter);
}

SIGNAL* counterClock(COUNTER* counter) {
   assert(counter != NULL);
   return counter->clk;
}

void counterConnect(COUNTER* counter, int oIndex, SIGNAL* signal) {
   assert(counter != NULL);
   assert(signal != NULL);
   assert(oIndex >= 0 && oIndex <= 3);
   counter->out[oIndex] = signal;
}

SIGNAL* counterReset(COUNTER* counter) {
   assert(counter != NULL);
   return counter->rst;
}

void counterHandler(void* block) {
   COUNTER* counter = block;
   assert(counter != NULL);

   /* TODO this isn't real behavior */
   if (signalRead(counter->rst) == LOW) {
      counter->next = 0;
   }

   if (signalRead(counter->clk) == HIGH) {
      if (counter->next != -1) {
         counter->next++;
         counter->next %= 16;
      }
   } else if (signalRead(counter->clk) == LOW) {
      int i;
      for (i = 0; i < 4; i++) {
         SIGVAL out;
         if (counter->next == -1) {
            out = UNKNOWN;
         } else {
            out = counter->next & (1 << i) ? HIGH : LOW;
         }
         if (counter->out[i] != NULL) {
            signalWrite(counter->out[i], out, counter->outID[i]);
         }
      }
   }
}
