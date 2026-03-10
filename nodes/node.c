#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node node_constructor(void *data, unsigned long dataSize) {

        if (dataSize < 0) {
                printf("Invalid dataSize for the Node");
                exit(1);
        }
        
        struct Node newNode;

        newNode.data = malloc(dataSize);
        memcpy(newNode.data, data, dataSize);

        newNode.next = NULL;
        newNode.previous = NULL;

        return newNode;
}


void node_destructor(struct Node *node) {

        free(node->data);
        free(node);
}
