
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node *create_node_bst(void *data, unsigned long data_size);
void destroy_node(struct Node *node_to_destroy);
struct Node *iterate_bst(struct binary_search_tree *binary_search_tree,
                         struct Node *element,void *data, int *direction);
void recursive_tree_destruction(struct Node *node_to_destroy);

void *search_bst(struct binary_search_tree *binary_search_tree, void *data);
void insert_bst(struct binary_search_tree *binary_search_tree, void *data,
                unsigned long data_size);

struct binary_search_tree
binary_search_tree_constructor(int (*compare)(void *data_one, void *data_two)) {
  struct binary_search_tree binary_search_tree;
  binary_search_tree.head = NULL;

  binary_search_tree.compare = compare;
  binary_search_tree.search = search_bst;
  binary_search_tree.insert = insert_bst;
  return binary_search_tree;
}

void binary_search_tree_destructor(
    struct binary_search_tree binary_search_tree) {
  recursive_tree_destruction(binary_search_tree.head);
}

struct Node *create_node_bst(void *data, unsigned long data_size) {

  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
  *new_node = node_constructor(data, data_size);
  return new_node;
}

void destroy_node_bst(struct Node *node_to_destroy) {
  node_destructor(node_to_destroy);
}

struct Node *iterate_bst(struct binary_search_tree *tree, struct Node *element, void *data, int *direction) {

        if (tree->compare(element->data, data) == 1) {
                
                if (element->next) {
                        return iterate_bst(tree, element->next, data, direction);
                }
                else {
                        *direction = 1;
                        return element;
                }
        }
        else if(tree->compare(element->data, data) == -1){
                
                if (element->previous) {
                        return iterate_bst(tree,element->previous, data,direction);
                }
                else {
                        *direction = -1;
                        return element;
                }
        }
        else {
                *direction = 0;
                return element;
        }
}

void recursive_tree_destruction(struct Node *node) {
        if (node->previous) {
                recursive_tree_destruction(node->previous);
        }
        else {
                recursive_tree_destruction(node->next);
        }
        destroy_node(node);
}

void insert_bst(struct binary_search_tree *tree, void *data, unsigned long data_size) {
        
        if (!tree->head) {
                tree->head = create_node_bst(data,data_size);
        }
        else {
                int direction = 0;        
                struct Node *element = iterate_bst(tree, tree->head, data, &direction);

                if (direction == 1) {
                        element->next = create_node_bst(data, data_size);
                } else {
                        element->previous = create_node_bst(data, data_size);
                }
        }
}





