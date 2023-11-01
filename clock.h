#pragma once

struct Clock;
struct Signal;

struct Clock* clockNew(void);
void clockFree(struct Clock*);

void clockConnect(struct Clock*, struct Signal*);
void clockRun(struct Clock*, int cycleCount);
