#pragma once

/*
 A SignalSet provides easy access to a group of signals, plus convenience
 methods for working with the group.
 */
struct SignalSet;

/* create a signal set with the specified size */
struct SignalSet* signalSetNew(unsigned int);

/* clean up a signal set */
void signalSetFree(struct SignalSet*);

/* get access to a member of a signal set */
struct Signal* signalSetAt(struct SignalSet*, unsigned int);

/* map an existing signal into a signal set */
void signalSetMap(struct SignalSet*, unsigned int, struct Signal*);
