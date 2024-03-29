#pragma once

#include "signalvalue.h"

struct Signal;

struct Signal* signalNew(void* block, void (*handler)(void*));
void signalFree(struct Signal*);

void signalPropagate(void);
enum SignalValue signalRead(struct Signal*);
void signalWrite(struct Signal*, enum SignalValue, int writer);
