#include "signal.h"

#include <assert.h>
#include <stdlib.h>

struct Signal {
   /* the signal's value */
   enum SignalValue value;

   /* writer ID number to associate writers with signals */
   unsigned int writer;

   /* the device that changes when the signal changes */
   void* block;

   /* the code that runs when the signal changes */
   void (*handler)(void*);
};

struct SignalNode {
   struct Signal* signal;
   struct SignalNode* next;
};

static struct SignalNode* signals = NULL;

/*
 Create a new signal with an unassigned writer ID, unknown value, and the
 provided block device and handler code.  When the signal changes, the handler
 is called with the device so that the device modeled by the handler code runs
 with the initial state defined by the block structure.
 */
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

/*
 Update the signal with the provided value, checking that the writer has not
 changed.  If the signal value changes from its previous value, add it to the
 list of signals to be propagated through the system.
 */
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
