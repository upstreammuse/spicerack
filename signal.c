#include "signal.h"

#include <assert.h>
#include <stdlib.h>

typedef struct Signal SIGNAL;
typedef struct SignalNode NODE;
typedef enum SignalValue SIGVAL;

struct Signal {
   SIGVAL value;
   unsigned int writer;
   void* block;
   void (*handler)(void*);
};

struct SignalNode {
   SIGNAL* signal;
   NODE* next;
};

static NODE* signals = NULL;

SIGNAL* signalNew(void* block, void (*handler)(void*)) {
   SIGNAL* signal = malloc(sizeof (SIGNAL));
   assert(block != NULL);
   assert(handler != NULL);
   signal->value = UNKNOWN;
   signal->writer = -1;
   signal->block = block;
   signal->handler = handler;
   return signal;
}

void signalFree(SIGNAL* signal) {
   free(signal);
}

void signalPropagate(void) {
   while (signals != NULL) {
      NODE* node = signals;
      signals = signals->next;
      node->signal->handler(node->signal->block);
      free(node);
   }
}

SIGVAL signalRead(SIGNAL* signal) {
   assert(signal != NULL);
   return signal->value;
}

void signalWrite(struct Signal* signal, enum SignalValue value,
                 unsigned int writer) {
   assert(signal != NULL);
   assert(signal->writer == (unsigned int)-1 || signal->writer == writer);
   signal->writer = writer;
   if (signal->value != value) {
      NODE* node = malloc(sizeof (NODE));
      signal->value = value;
      node->signal = signal;
      node->next = signals;
      signals = node;
   }
}
