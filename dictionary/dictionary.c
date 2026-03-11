
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node *create_node_bst(void *data, unsigned long data_size);
void destroy_node(struct Node *node_to_destroy);
struct Node *iterate_bst(struct binary_search_tree *binary_search_tree,
                         struct Node *element, int *direction);
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

  struct Node new_node = (struct Node *)malloc(sizeof(Node));
  *new_node = node_constructor(data, data_size);
  return new_node;
}

void destroy_node_bst(struct Node *node_to_destroy) {
  node_destructor(node_to_destroy);
}
