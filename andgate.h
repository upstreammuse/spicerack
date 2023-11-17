#pragma once

#include "signalvalue.h"

struct AndGate;
struct Signal;

struct AndGate* andGateNew(void);
void andGateFree(struct AndGate*);

void andGateConnect(struct AndGate*, struct Signal*);
struct Signal* andGateInputA(struct AndGate*);
struct Signal* andGateInputB(struct AndGate*);
