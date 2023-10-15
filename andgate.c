#include "andgate.h"

#include "spicerack.h"

#include <assert.h>
#include <stdlib.h>

void andGateHandler(void*);
const int AND_GATE_MAGIC = 0x4155a3dd;

struct AndGate {
   int magic;
   struct InputLine* A;
   struct InputLine* B;
   struct InputLine* O;
   int OID;
};

struct AndGate* allocateAndGate(void) {
   struct AndGate* andGate_ = malloc(sizeof (struct AndGate));
   andGate_->magic = AND_GATE_MAGIC;
   andGate_->A = allocateInput(andGate_, andGateHandler);
   andGate_->B = allocateInput(andGate_, andGateHandler);
   andGate_->O = NULL;
   andGate_->OID = allocateOutput();
   return andGate_;
}

void andGateHandler(void* block) {
   int* magic = block;
   struct AndGate* gate = block;
   enum SignalValue A;
   enum SignalValue B;
   enum SignalValue O = UNKNOWN;

   assert(magic != NULL);
   assert(gate != NULL);
   assert(*magic == AND_GATE_MAGIC);

   A = inputLineGet(gate->A);
   B = inputLineGet(gate->B);

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

   inputLineSet(gate->O, O, gate->OID);
   inputLineHandled(gate->A);
   inputLineHandled(gate->B);
}

void connectAndGate(struct AndGate* gate, struct InputLine* next) {
   assert(gate != NULL);
   assert(next != NULL);
   gate->O = next;
}

void testAndGate(struct AndGate* gate, enum SignalValue inA, enum SignalValue inB) {
   static int writerA = 46546;
   static int writerB = 94945;
   inputLineSet(gate->A, inA, writerA);
   inputLineSet(gate->B, inB, writerB);
   propagate();
}
