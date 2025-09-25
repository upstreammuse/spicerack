#pragma once

#include "signalvalue.h"

/* A signal is a 'wire' in the system that can have a value */
struct Signal;

/* create a new signal */
struct Signal* signalNew(void* block, void (*handler)(void*));

/* destroy a signal */
void signalFree(struct Signal*);

/* propagate all pending signals to get to the next quiescent state */
void signalPropagate(void);

/* get the value of a signal */
enum SignalValue signalRead(struct Signal*);

/* write a value to a signal */
void signalWrite(struct Signal*, enum SignalValue, unsigned int writer);
