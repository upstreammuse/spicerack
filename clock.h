#pragma once

#include "spicerack.h"

struct Clock;
typedef struct Clock CLOCK;

CLOCK* clockNew(void);
void clockFree(CLOCK*);

void clockConnect(CLOCK*, struct InputLine*);
void clockRun(CLOCK*, int cycleCount);
