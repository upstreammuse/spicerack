#pragma once

enum SignalValue {
   UNKNOWN,
   LOW,
   HIGH,
   HIGH_Z
};

char* signalValueStr(enum SignalValue);
