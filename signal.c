#include "signal.h"

#include <assert.h>
#include <stdlib.h>

typedef struct Signal SIGNAL;
typedef enum SignalValue SIGVAL;

struct Signal {
   char changed;
   SIGVAL value;
   int writer;
   void* block;
   void (*handler)(void*);
};

/* TODO decide how to handle allocation, maybe just stick with malloc for now */
SIGNAL inputs[1000];
int nextInput = 0;

/* TODO realloc or fail when over the array size limit */
SIGNAL* signalNew(void* block, void (*handler)(void*)) {
   int i = nextInput++;
   assert(block != NULL);
   assert(handler != NULL);
   inputs[i].changed = 1;
   inputs[i].value = HIGH_Z;
   inputs[i].writer = -1;
   inputs[i].block = block;
   inputs[i].handler = handler;
   return inputs + i;
}

void signalFree(SIGNAL* signal) {
   (void)signal;
   /* do nothing for now */
}

char signalChanged(SIGNAL* signal) {
   assert(signal != NULL);
   return signal->changed;
}

void signalHandled(SIGNAL* signal) {
   assert(signal != NULL);
   signal->changed = 0;
}

void signalPropagate(void) {
   int goAgain = 0;
   do {
      int i;
      goAgain = 0;
      for (i = 0; i < nextInput; i++) {
         if (inputs[i].changed) {
            goAgain = 1;
            inputs[i].handler(inputs[i].block);
            inputs[i].changed = 0;
         }
      }
   } while(goAgain);
}

SIGVAL signalRead(SIGNAL* signal) {
   assert(signal != NULL);
   return signal->value;
}

void signalWrite(SIGNAL* signal, SIGVAL value, int writer) {
   assert(signal != NULL);
   assert(signal->writer == -1 || signal->writer == writer);
   if (signal->value != value) {
      signal->changed = 1;
      signal->value = value;
      signal->writer = writer;
   }
}
