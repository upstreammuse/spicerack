#pragma once

#include "spicerack.h"

struct AndGate;

struct AndGate* allocateAndGate(void);
void connectAndGate(struct AndGate*, struct InputLine*);
void testAndGate(struct AndGate*, enum SignalValue, enum SignalValue);
