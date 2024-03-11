#pragma once

struct Watcher;

struct Watcher* watcherNew(char const* label);
void watcherFree(struct Watcher*);

struct Signal* watcherClock(struct Watcher*);
struct Signal* watcherInput(struct Watcher*);
