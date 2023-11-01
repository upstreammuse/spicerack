#pragma once

struct AndGate;
struct Signal;
enum SignalValue;

struct AndGate* allocateAndGate(void);
void connectAndGate(struct AndGate*, struct Signal*);
void testAndGate(struct AndGate*, enum SignalValue, enum SignalValue);
