#pragma once

struct Counter;

struct Counter* counterNew(void);
void counterFree(struct Counter*);

struct Signal* counterClock(struct Counter*);
void counterConnect(struct Counter*, int, struct Signal*);
struct Signal* counterReset(struct Counter*);
