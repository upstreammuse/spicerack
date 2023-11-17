#include "andgate.h"

#include "signal.h"

#include <assert.h>
#include <stdlib.h>

typedef struct AndGate ANDGATE;
typedef struct Signal SIGNAL;
typedef enum SignalValue SIGVAL;

void andGateHandler(void*);

/* TODO either make this dynamically assigned, or need a central repository */
const int AND_GATE_MAGIC = 0x4155a3dd;

struct AndGate {
   int magic;
   SIGNAL* A;
   SIGNAL* B;
   SIGNAL* O;
   int OID;
};

ANDGATE* andGateNew(void) {
   ANDGATE* gate = malloc(sizeof (ANDGATE));
   gate->magic = AND_GATE_MAGIC;
   gate->A = signalNew(gate, andGateHandler);
   gate->B = signalNew(gate, andGateHandler);
   gate->O = NULL;
   gate->OID = allocateOutput();
   return gate;
}

void andGateFree(ANDGATE* gate) {
   if (gate == NULL) return;
   assert(gate->magic == AND_GATE_MAGIC);
   signalFree(gate->A);
   signalFree(gate->B);
   signalFree(gate->O);
   free(gate);
}

void andGateConnect(ANDGATE* gate, SIGNAL* output) {
   assert(gate != NULL);
   assert(gate->magic == AND_GATE_MAGIC);
   assert(output != NULL);
   gate->O = output;
}

SIGNAL* andGateInputA(ANDGATE* gate) {
   assert(gate != NULL);
   assert(gate->magic == AND_GATE_MAGIC);
   return gate->A;
}

SIGNAL* andGateInputB(ANDGATE* gate) {
   assert(gate != NULL);
   assert(gate->magic == AND_GATE_MAGIC);
   return gate->B;
}

void testAndGate(ANDGATE* gate, SIGVAL inA, SIGVAL inB) {
   static int writerA = 46546;
   static int writerB = 94945;
   signalWrite(gate->A, inA, writerA);
   signalWrite(gate->B, inB, writerB);
   propagate();
}

void andGateHandler(void* block) {
   ANDGATE* gate = block;
   SIGVAL A;
   SIGVAL B;
   SIGVAL O = UNKNOWN;

   assert(gate != NULL);
   assert(gate->magic == AND_GATE_MAGIC);

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
   signalHandled(gate->A);
   signalHandled(gate->B);
}
