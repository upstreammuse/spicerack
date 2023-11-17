#include "signalvalue.h"

typedef enum SignalValue SIGVAL;

char* signalValueStr(SIGVAL val) {
   switch (val) {
      case UNKNOWN:
         return "[unknown]";
      case HIGH:
         return "[high]";
      case LOW:
         return "[low]";
      case HIGH_Z:
         return "[highZ]";
   }
}
