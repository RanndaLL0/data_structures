#include "entry.h"
#include <stdlib.h>
#include <string.h>


struct entry entry_constructor(void *key , unsigned long key_size, void *value, unsigned long value_size) {

        struct entry entry;

        entry.key = malloc(key_size);
        entry.value = malloc(value_size);
        
        memcpy(entry.key, key, key_size);
        memcpy(entry.value, value, value_size);

        return entry;
}

void entry_destructor(struct entry *entry) {
        free(entry->key);
        free(entry->value);
        free(entry);
}
