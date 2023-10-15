#include "andgate.h"
#include "clock.h"

#include <stdio.h>

struct Debugger {
   struct InputLine* I;
};

void debugHandler(void* block) {
   struct Debugger* d = block;
   printf("%d %d\n", inputLineIsChanged(d->I), inputLineGet(d->I));
   inputLineHandled(d->I);
}

int main(void) {
   CLOCK* clock = clockNew();
   struct Debugger d;
   d.I = allocateInput(&d, debugHandler);
   /*
    struct AndGate* and1 = allocateAndGate();
    connectAndGate(and1, d.I);
    testAndGate(and1, HIGH, HIGH);
    */
   clockConnect(clock, d.I);
   clockRun(clock, 2);

   return 0;
}
