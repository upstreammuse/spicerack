# spicerack

## signals

Spicerack supports four signal levels, HIGH, LOW, UNKNOWN, and HIGH_Z.  These
are sufficient to model basic digital levels.

Signals have a value.  A signal can be written to to change its value.  When a
signal receives a value change, that triggers the signal's handler to fire with
the signal's block.  Thus any signal change becomes an event that causes a block
to process its inputs.

During the signal propagation phase, each signal with a pending signal change
stimulates its associated handler with its associated block.  This may cause
additional signals to fire.  Eventually the design stabilizes, and thus the
system is digitally quiescent.  Once there, the clock can tick to trigger the
next cascade of updates.
