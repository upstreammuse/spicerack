#include "signal.h"

#include <assert.h>
#include <stdlib.h>

struct Signal {
   enum SignalValue value;
   unsigned int writer;
   void* block;
   void (*handler)(void*);
};

struct SignalNode {
   struct Signal* signal;
   struct SignalNode* next;
};

static struct SignalNode* signals = NULL;

struct Signal* signalNew(void* block, void (*handler)(void*)) {
   struct Signal* signal = malloc(sizeof (struct Signal));
   assert(block != NULL);
   assert(handler != NULL);
   signal->value = UNKNOWN;
   signal->writer = -1;
   signal->block = block;
   signal->handler = handler;
   return signal;
}

void signalFree(struct Signal* signal) {
   free(signal);
}

void signalPropagate(void) {
   while (signals != NULL) {
      struct SignalNode* node = signals;
      signals = signals->next;
      node->signal->handler(node->signal->block);
      free(node);
   }
}

enum SignalValue signalRead(struct Signal* signal) {
   assert(signal != NULL);
   return signal->value;
}

void signalWrite(struct Signal* signal, enum SignalValue value,
                 unsigned int writer) {
   assert(signal != NULL);
   assert(signal->writer == (unsigned int)-1 || signal->writer == writer);
   signal->writer = writer;
   if (signal->value != value) {
      struct SignalNode* node = malloc(sizeof (struct SignalNode));
      signal->value = value;
      node->signal = signal;
      node->next = signals;
      signals = node;
   }
}
