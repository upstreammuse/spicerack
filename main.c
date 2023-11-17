#include "andgate.h"
#include "clock.h"
#include "signal.h"

#include <stdio.h>

struct Debugger {
   struct Signal* I;
};

void debugHandler(void* block) {
   struct Debugger* d = block;
   printf("%d %s\n", signalChanged(d->I), signalValueStr(signalRead(d->I)));
   signalHandled(d->I);
}

int main(void) {
   struct Clock* clock;
   struct Debugger d1;
   struct AndGate* and1;
   struct Debugger d2;

   printf("clock test\n");
   clock = clockNew();
   d1.I = signalNew(&d1, debugHandler);
   clockConnect(clock, d1.I);
   clockRun(clock, 2);
   clockFree(clock);

   printf("and test\n");
   and1 = andGateNew();
   d2.I = signalNew(&d2, debugHandler);
   andGateConnect(and1, d2.I);
   testAndGate(and1, HIGH, HIGH);
   andGateFree(and1);

   return 0;
}
