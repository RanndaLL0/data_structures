#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

/*
 *      PRIVATE MEMBERS
 *
 * */

struct Node *create_node_ll(void *data, unsigned long dataSize);
struct Node *destroy_node_ll(struct Node *node);

/* 
 *      PROTOTYPES
 *
 * */

struct Node* iterate_ll(struct linked_list *list, int index);
void insert_ll(struct linked_list *list,int index, void *data, unsigned long dataSize);
void remove_node_ll(struct linked_list *list, int index);
void *retrieve_node_ll(struct linked_list *list, int index);
void bubble_sort_ll(struct linked_list *list, int (* compare)(void *a, void *b));
short binary_search_ll(struct linked_list *list, void *query, int (*compare)(void *a, void *b));

struct linked_list linked_list_constructor() {
        struct linked_list newList; 

        newList.head = NULL;
        newList.length = 0;

        newList.insert = insert_ll;
        newList.remove = remove_node_ll;
        newList.sort = bubble_sort_ll;
        newList.search = binary_search_ll;
        return newList;
}

void linked_list_destructor(struct linked_list *linked_list) {

        for(int i = 0; i < linked_list->length; i++) {
                linked_list->remove(linked_list, 0 );
        }
}

struct Node* create_node_ll(void *data, unsigned long dataSize) {

        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        *newNode = node_constructor(data, dataSize);
        return newNode;
}

void node_destructor(struct Node *node) {
        node_destructor(node);
}

struct Node* iterate_ll(struct linked_list *list, int index) {

        if (index <= 0 || index > list->length) {
                return NULL;
        }

        struct Node* element = list->head;

        for(int i = 0; i < index; i++) {
                element = element->next;
        }

        return element;

}

void insert_ll(struct linked_list *linked_list, int index, void *data, unsigned long dataSize) {
       struct Node *node_to_insert = create_node_ll(data, dataSize);

        if (index == 0) {
                node_to_insert->next = linked_list->head;
                linked_list->head = node_to_insert;
        } 
        else {
                struct Node *element = iterate_ll(linked_list, index);
                node_to_insert->next = element->next;
                element->next = node_to_insert;
        }

        linked_list->length += 1;
}

void remove_node_ll(struct linked_list *linked_list, int index) {
        
        if (index == 0) {
                struct Node *node_to_remove = linked_list->head;

                if (node_to_remove) {
                        linked_list->head = node_to_remove->next;
                        destroy_node_ll(node_to_remove);
                }
        }
        else {
                struct Node *element = iterate_ll(linked_list, index-1);
                struct Node *node_to_remove = element->next;

                element->next = node_to_remove->next;

                destroy_node_ll(node_to_remove);
        }

        linked_list->length -= 1;
}

void *retrieve_all(struct linked_list *linked_list, int index) {

        struct Node *cursor = iterate_ll(linked_list, index);

        if(cursor) {
                return cursor->data;
        }
        else {
                return NULL;
        }
}

/*
 *      Other sort algorithm's will be implementate soon
 * */
void bubble_sort_ll(struct linked_list *linked_list, int (*compare)(void *a, void *b)) {
        
        for (struct Node *i = linked_list->retrieve(linked_list, 0); i; i = i->next) {
                for(struct Node *n = i->next; n; n = n->next) {
                        if ((compare(i->data, n->data)) > 0) {
                                // swap
                                void *temporary = n->data;
                                n->data = i->data;
                                i->data = temporary;
                        }
                }
        }
}

short binary_search_ll(struct linked_list *linked_list, void *query, int (*compare)(void *a, void *b)) {

        int position = linked_list->length/2;
        int min_checked = 0;
        int max_checked = linked_list->length;

        while(max_checked > min_checked) {
                
                void *data = linked_list->retrieve(linked_list, position);

                if (compare(data, query) == 1) {
                        max_checked = position;

                        if (position != (min_checked + position) / 2) {
                                position = (min_checked + position) / 2;
                        }
                        else {
                                break;
                        }
                }
                else if (compare(data, query) == -1) {
                        min_checked = position;

                        if (position != (max_checked + position) / 2) {
                                position = (max_checked + position) / 2;
                        }
                        else {
                                break;
                        }
                }
                else {
                        return 1;
                }
        }
        return 0;
}
