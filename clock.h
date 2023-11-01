#pragma once

struct Clock;
typedef struct Clock CLOCK;
struct Signal;

CLOCK* clockNew(void);
void clockFree(CLOCK*);

void clockConnect(CLOCK*, struct Signal*);
void clockRun(CLOCK*, int cycleCount);
