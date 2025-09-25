#pragma once

/* The values that a signal can have */
enum SignalValue {
   UNKNOWN,
   LOW,
   HIGH,
   HIGH_Z
};

/* Get a signal value as a human readable string */
char* signalValueStr(enum SignalValue);
