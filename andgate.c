#include "andgate.h"

#include "output.h"
#include "signal.h"

#include <assert.h>
#include <stdlib.h>

static void andGateHandler(void*);

struct AndGate {
   int OID;
   struct Signal* A;
   struct Signal* B;
   struct Signal* O;
};

struct AndGate* andGateNew(void) {
   struct AndGate* gate = malloc(sizeof (struct AndGate));
   gate->A = signalNew(gate, andGateHandler);
   gate->B = signalNew(gate, andGateHandler);
   gate->O = NULL;
   gate->OID = allocateOutput();
   return gate;
}

void andGateFree(struct AndGate* gate) {
   if (gate == NULL) return;
   signalFree(gate->A);
   signalFree(gate->B);
   free(gate);
}

void andGateConnect(struct AndGate* gate, struct Signal* output) {
   assert(gate != NULL);
   assert(output != NULL);
   assert(gate->O == NULL);
   gate->O = output;
}

struct Signal* andGateInputA(struct AndGate* gate) {
   assert(gate != NULL);
   return gate->A;
}

struct Signal* andGateInputB(struct AndGate* gate) {
   assert(gate != NULL);
   return gate->B;
}

static void andGateHandler(void* block) {
   struct AndGate* gate = block;
   enum SignalValue A, B, O = UNKNOWN;

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
