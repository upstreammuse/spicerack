#include "watcher.h"

#include "signal.h"
#include "signalvalue.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Signal SIGNAL;
typedef enum SignalValue SIGVAL;
typedef struct Watcher WATCHER;

void watcherHandler(void*);

struct Watcher {
   SIGNAL* clock;
   size_t clockCount;
   SIGNAL* input;
   char const* label;
   SIGVAL lastClock;
   SIGVAL lastInput;
};

WATCHER* watcherNew(char const* label) {
   WATCHER* w = malloc(sizeof (WATCHER));
   w->clock = signalNew(w, watcherHandler);
   w->clockCount = -1;
   w->input = signalNew(w, watcherHandler);
   w->label = strdup(label);
   w->lastClock = LOW;
   w->lastInput = UNKNOWN;
   return w;
}

void watcherFree(WATCHER* w) {
   if (w == NULL) return;
   signalFree(w->clock);
   signalFree(w->input);
   free((char*)w->label);
   free(w);
}

SIGNAL* watcherClock(WATCHER* w) {
   return w->clock;
}

SIGNAL* watcherInput(WATCHER* w) {
   return w->input;
}

void watcherHandler(void* block) {
   WATCHER* w = block;
   SIGVAL C;
   SIGVAL I;

   assert(w != NULL);
   C = signalRead(w->clock);
   I = signalRead(w->input);

   if (C != LOW && C != HIGH) {
      printf("[%s](%lu) ** Clock malfunction from %s to %s\n", w->label,
             w->clockCount, signalValueStr(w->lastClock), signalValueStr(C));
   }
   if (w->lastClock == LOW && C == HIGH) {
      w->clockCount++;
   }
   w->lastClock = C;

   if (w->lastInput != I) {
      printf("[%s](%lu) %s\n", w->label, w->clockCount, signalValueStr(I));
      w->lastInput = I;
   }
}
