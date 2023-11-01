#include "andgate.h"
#include "clock.h"
#include "signal.h"

#include <stdio.h>

struct Debugger {
   struct Signal* I;
};

void debugHandler(void* block) {
   struct Debugger* d = block;
   printf("%d %d\n", signalChanged(d->I), signalRead(d->I));
   signalHandled(d->I);
}

int main(void) {
   CLOCK* clock = clockNew();
   struct Debugger d;
   d.I = signalNew(&d, debugHandler);
   /*
    struct AndGate* and1 = andGateNew();
    connectAndGate(and1, d.I);
    testAndGate(and1, HIGH, HIGH);
    andGateFree(and1);
    */
   clockConnect(clock, d.I);
   clockRun(clock, 2);

   return 0;
}
