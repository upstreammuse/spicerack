#pragma once

enum SignalValue {
   UNKNOWN,
   LOW,
   HIGH,
   HIGH_Z
};

struct Signal;
typedef struct Signal SIGNAL;

SIGNAL* signalNew(void* block, void (*handler)(void*));
void signalFree(SIGNAL*);

void signalWrite(SIGNAL*, enum SignalValue, int writer);
int signalChanged(SIGNAL*);
enum SignalValue signalRead(SIGNAL*);
void signalHandled(SIGNAL*);
