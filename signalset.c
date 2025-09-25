#include "signalset.h"

#include "signal.h"

#include <assert.h>
#include <stdlib.h>

struct SignalSetItem {
   struct Signal* signal;
   int mapped;
   int used;
};

struct SignalSet {
   unsigned int size;
   struct SignalSetItem* items;
};

static void signalSetHandler(void* block) {
   (void)block;
}

struct SignalSet* signalSetNew(unsigned int size) {
   unsigned int i;
   struct SignalSet* set = malloc(sizeof (struct SignalSet));
   set->size = size;
   set->items = malloc(sizeof (struct SignalSetItem) * size);
   for (i = 0; i < size; i++) {
      set->items[i].signal = signalNew(set, signalSetHandler);
      set->items[i].mapped = 0;
      set->items[i].used = 0;
   }
   return set;
}

void signalSetFree(struct SignalSet* set) {
   unsigned int i;
   if (set == NULL) return;
   for (i = 0; i < set->size; i++) {
      if (!set->items[i].mapped) {
         signalFree(set->items[i].signal);
      }
   }
   free(set->items);
   free(set);
}

struct Signal* signalSetAt(struct SignalSet* set, unsigned int index) {
   assert(set != NULL);
   assert(index < set->size);
   set->items[index].used = 1;
   return set->items[index].signal;
}

void signalSetMap(struct SignalSet* set, unsigned int index,
                  struct Signal* signal) {
   assert(set != NULL);
   assert(index < set->size);
   assert(signal != NULL);
   assert(!set->items[index].used);
   if (!set->items[index].mapped) {
      signalFree(set->items[index].signal);
   }
   set->items[index].signal = signal;
   set->items[index].mapped = 1;
}
