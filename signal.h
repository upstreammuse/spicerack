#pragma once

#include "signalvalue.h"

struct Signal;
typedef struct Signal SIGNAL;

SIGNAL* signalNew(void* block, void (*handler)(void*));
void signalFree(SIGNAL*);

void signalWrite(SIGNAL*, enum SignalValue, int writer);
char signalChanged(SIGNAL*);
enum SignalValue signalRead(SIGNAL*);
void signalHandled(SIGNAL*);

int allocateOutput(void);
void propagate(void);
