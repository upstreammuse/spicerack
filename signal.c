#include "signal.h"

#include <assert.h>
#include <stdlib.h>

char* signalValueStr(enum SignalValue val) {
   switch (val) {
      case UNKNOWN:
         return "[unknown]";
      case HIGH:
         return "[high]";
      case LOW:
         return "[low]";
      case HIGH_Z:
         return "[highZ]";
   }
}

struct Signal {
   char changed;
   enum SignalValue value;
   int writer;
   void* block;
   void (*handler)(void*);
};

/* TODO decide how to handle allocation, maybe just stick with malloc for now */
struct Signal inputs[1000];
int nextInput = 0;
int nextOutput = 1000;

/* TODO realloc or fail when over the array size limit */
struct Signal* signalNew(void* block, void (*handler)(void*)) {
   int i = nextInput++;
   inputs[i].changed = 1;
   inputs[i].value = HIGH_Z;
   inputs[i].writer = -1;
   inputs[i].handler = handler;
   inputs[i].block = block;
   return inputs + i;
}

void signalFree(struct Signal* signal) {
   (void)signal;
   // do nothing for now
}

/* TODO fail when wrapping around? */
int allocateOutput(void) {
   return nextOutput++;
}

enum SignalValue signalRead(struct Signal* line) {
   assert(line != NULL);
   return line->value;
}

void signalHandled(struct Signal* line) {
   assert(line != NULL);
   line->changed = 0;
}

char signalChanged(struct Signal* line) {
   assert(line != NULL);
   return line->changed;
}

void signalWrite(struct Signal* line, enum SignalValue value, int output) {
   assert(line != NULL);
   assert(line->writer == -1 || line->writer == output);
   assert(line->handler != NULL);
   assert(line->block != NULL);
   if (line->value != value) {
      line->changed = 1;
      line->value = value;
      line->writer = output;
   }
}

void propagate(void) {
   int goAgain = 0;
   do {
      int i;
      goAgain = 0;
      for (i = 0; i < nextInput; i++) {
         if (inputs[i].changed) {
            goAgain = 1;
            assert(inputs[i].handler != NULL);
            assert(inputs[i].block != NULL);
            inputs[i].handler(inputs[i].block);
            inputs[i].changed = 0;
         }
      }
   } while(goAgain);
}
