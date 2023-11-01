#pragma once

struct AndGate;
struct Signal;
enum SignalValue;

struct AndGate* andGateNew(void);
void andGateFree(struct AndGate*);

void andGateConnect(struct AndGate*, struct Signal*);
void testAndGate(struct AndGate*, enum SignalValue, enum SignalValue);
