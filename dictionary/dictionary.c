#include "dictionary.h"
#include "../linked_list/linked_list.h"
#include "../trees/tree.h"
#include "entry.h"
#include <stdlib.h>
#include <string.h>

void recursive_dictionary_destroy(struct Node *cursor);

void insert_dict(struct dictionary *dictionary, void *key, unsigned long key_size, void *value, unsigned long value_size);
void * search_dict(struct dictionary *dictionary, void *key, unsigned long key_size);

struct dictionary dictionary_constructor(int (*compare)(void *key_one, void *key_two))
{
    struct dictionary dictionary;
    dictionary.binary_search_tree = binary_search_tree_constructor(compare);
    dictionary.keys = linked_list_constructor();
    dictionary.insert = insert_dict;
    dictionary.search = search_dict;
    return dictionary;
}

void dictionary_destructor(struct dictionary *dictionary)
{
    linked_list_destructor(&dictionary->keys);
    recursive_dictionary_destroy(dictionary->binary_search_tree.head);
}

void recursive_dictionary_destroy(struct Node *cursor)
{
    if (cursor->previous)
    {
        recursive_dictionary_destroy(cursor->previous);
    }
    if (cursor->next)
    {
        recursive_dictionary_destroy(cursor->next);
    }
    entry_destructor((struct entry *)cursor->data);
    free(cursor->data);
    free(cursor);
}


void * search_dict(struct dictionary *dictionary, void *key, unsigned long key_size)
{
    int dummy_value = 0;
    struct entry searchable = entry_constructor(key, key_size, &dummy_value, sizeof(dummy_value));
    void * result = dictionary->binary_search_tree.search(&dictionary->binary_search_tree, &searchable);
    if (result)
    {
        return ((struct entry *)result)->value;
    }
    else
    {
        return NULL;
    }
}

void insert_dict(struct dictionary *dictionary, void *key, unsigned long key_size, void *value, unsigned long value_size)
{
    struct entry entry = entry_constructor(key, key_size, value, value_size);
    dictionary->binary_search_tree.insert(&dictionary->binary_search_tree, &entry, sizeof(entry));
    dictionary->keys.insert(&dictionary->keys, dictionary->keys.length, key, key_size);
}


int compare_string_keys(void *entry_one, void *entry_two)
{
    if (strcmp((char *)(((struct entry *)entry_one)->key), (char *)(((struct entry *)entry_two)->key)) > 0)
    {
        return 1;
    }
    else if (strcmp((char *)(((struct entry *)entry_one)->key), (char *)(((struct entry *)entry_two)->key)) < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
