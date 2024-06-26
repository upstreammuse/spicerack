#include "andgate.h"

#include "output.h"
#include "signal.h"

#include <assert.h>
#include <stdlib.h>

typedef struct AndGate ANDGATE;
typedef struct Signal SIGNAL;
typedef enum SignalValue SIGVAL;

static void andGateHandler(void*);

struct AndGate {
   SIGNAL* A;
   SIGNAL* B;
   SIGNAL* O;
   int OID;
};

ANDGATE* andGateNew(void) {
   ANDGATE* gate = malloc(sizeof (ANDGATE));
   gate->A = signalNew(gate, andGateHandler);
   gate->B = signalNew(gate, andGateHandler);
   gate->O = NULL;
   gate->OID = allocateOutput();
   return gate;
}

void andGateFree(ANDGATE* gate) {
   if (gate == NULL) return;
   signalFree(gate->A);
   signalFree(gate->B);
   free(gate);
}

void andGateConnect(ANDGATE* gate, SIGNAL* output) {
   assert(gate != NULL);
   assert(output != NULL);
   assert(gate->O == NULL);
   gate->O = output;
}

SIGNAL* andGateInputA(ANDGATE* gate) {
   assert(gate != NULL);
   return gate->A;
}

SIGNAL* andGateInputB(ANDGATE* gate) {
   assert(gate != NULL);
   return gate->B;
}

static void andGateHandler(void* block) {
   ANDGATE* gate = block;
   SIGVAL A;
   SIGVAL B;
   SIGVAL O = UNKNOWN;

   assert(gate != NULL);
   if (gate->O == NULL) return;

   A = signalRead(gate->A);
   B = signalRead(gate->B);
   switch (A) {
      case UNKNOWN:
      case HIGH_Z:
         O = UNKNOWN;
         break;
      case LOW:
      case HIGH:
         switch (B) {
            case UNKNOWN:
            case HIGH_Z:
               O = UNKNOWN;
               break;
            case LOW:
            case HIGH:
               O = (A == HIGH && B == HIGH) ? HIGH : LOW;
               break;
         }
         break;
   }

   signalWrite(gate->O, O, gate->OID);
}
