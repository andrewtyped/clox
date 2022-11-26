#include <stdlib.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "table.h"
#include "value.h"

#define TABLE_MAX_LOAD 0.75

void initTable(Table* table) {
    table->count = 0;
    table->capacity = 0;
    table->entries = NULL;
}

void freeTable(Table* table) {
    FREE_ARRAY(Entry, table->entries, table->capacity);
    initTable(table);
}

static Entry* findEntry(Entry* entries, int capacity, ObjString* key) {
    //Optimization - We were using modulo here to ensure index fits in the array bounds. Modulo is 30-50x slower than addition on x86.
    //We **know** capacity is a power of two, so we can optimize - modulo in this case is equivalent to bitwise &, after subtracting one from
    //the second operand. Subtracting 1 from a power of 2 turns all lower bits to 1.
    uint32_t index = key->hash & (capacity - 1);
    Entry* tombstone = NULL;

    for(;;) {
        Entry* entry = &entries[index];
        if (entry->key == NULL) {
            if (IS_NIL(entry->value)) {
                //We didn't find the key. Return the tombstone, if any, so the caller can overwrite it with a new entry if they want to.
                return tombstone != NULL ? tombstone: entry;
            } else {
                if (tombstone == NULL) {
                    //We found a tombstone.
                    tombstone = entry;
                }
            }
        } else if (entry->key == key) {
            //We found the key.
            return entry;
        }

        index = (index + 1) & (capacity - 1);
    }
}

static void adjustCapacity(Table* table, int capacity) {
    Entry* entries = ALLOCATE(Entry, capacity);

    //Initialize the newly allocated hash table capacity
    for(int i = 0; i < capacity; i++) {
        entries[i].key = NULL;
        entries[i].value = NIL_VAL;
    }

    //copy existing entries over to the new, larger table.
    table->count = 0;
    for(int i = 0; i < table->capacity; i++) {
        Entry* entry = &table->entries[i];
        if (entry->key == NULL) {
            //Skip empty entries and tombstones.
            continue;
        }

        Entry* dest = findEntry(entries, capacity, entry->key);
        dest->key = entry->key;
        dest->value = entry->value;
        table->count++;
    }

    FREE_ARRAY(Entry, table->entries, table->capacity);
    table->entries = entries;
    table->capacity = capacity;
}

bool tableDelete(Table* table, ObjString* key) {
    if (table->count == 0) {
        return false;
    }

    Entry* entry = findEntry(table->entries, table->capacity, key);

    if (entry->key == NULL) {
        return false;
    }

    entry->key = NULL;
    entry->value = BOOL_VAL(true);
    return true;
}

bool tableGet(Table* table, ObjString* key, Value* value) {
    if (table->count == 0) {
        return false;
    }

    Entry* entry = findEntry(table->entries, table->capacity, key);

    if (entry->key == NULL) {
        return false;
    }

    *value = entry->value;
    return true;
}

bool tableSet(Table* table, ObjString* key, Value value) {
    if (table->count + 1 > table->capacity * TABLE_MAX_LOAD) {
        int capacity = GROW_CAPACITY(table->capacity);
        adjustCapacity(table, capacity);
    }

    Entry* entry = findEntry(table->entries, table->capacity, key);

    bool isNewKey = entry->key == NULL;

    //If the IS_NIL check fails, the entry we found is a tombstone, and is already accounted for in the array's capacity. We don't need to increment the count;
    if (isNewKey && IS_NIL(entry->value)) {
        table->count++;
    }

    entry->key = key;
    entry->value = value;
    return isNewKey;
}

void tableAddAll(Table* from, Table* to) {
    for (int i = 0; i < from->capacity; i++) {
        Entry* entry = &from->entries[i];
        if (entry->key != NULL) {
            tableSet(to, entry->key, entry->value);
        }
    }
}

ObjString* tableFindString(Table* table, const char* chars, int length, uint32_t hash) {
    if (table->count == 0) {
        return NULL;
    }

    uint32_t index = hash & (table->capacity - 1);
    for(;;) {
        Entry* entry = &table->entries[index];
        if (entry->key == NULL) {
            //Stop if we find an emptry non-tombstone entry.
            if (IS_NIL(entry->value)) {
                return NULL;
            }
        } else if (entry->key->length == length && 
                   entry->key->hash == hash &&
                   memcmp(entry->key->chars, chars, length) == 0) {
            // we found it
            return entry->key;
        }

        index = (index + 1) & (table->capacity - 1);

    }
}

void tableRemoveWhite(Table* table) {
    for (int i = 0; i < table->capacity; i++) {
        Entry* entry = &table->entries[i];

        if (entry->key != NULL && !entry->key->obj.isMarked) {
            tableDelete(table, entry->key);
        }
    }
}

void markTable(Table* table) {
    for (int i = 0; i <table->capacity; i++) {
        Entry* entry = &table->entries[i];
        markObject((Obj*)entry->key);
        markValue(entry->value);
    }
}