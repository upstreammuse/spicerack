#include "andgate.h"
#include "clock.h"
#include "signal.h"

#include <stdio.h>

struct Debugger {
   struct Signal* I;
};

void debugHandler(void* block) {
   struct Debugger* d = block;
   printf("%s\n", signalValueStr(signalRead(d->I)));
}

int main(void) {

   {
      struct Clock* clock;
      struct Debugger d;
      printf("clock test\n");
      clock = clockNew();
      d.I = signalNew(&d, debugHandler);
      clockConnect(clock, d.I);
      clockRun(clock, 2);
      clockFree(clock);
   }

   {
      struct Debugger d;
      int writerA = 46546;
      int writerB = 94945;
      struct AndGate* gate = andGateNew();
      printf("and test\n");
      d.I = signalNew(&d, debugHandler);
      andGateConnect(gate, d.I);
      signalWrite(andGateInputA(gate), HIGH, writerA);
      signalWrite(andGateInputB(gate), HIGH, writerB);
      signalPropagate();
      andGateFree(gate);
   }

   return 0;
}
