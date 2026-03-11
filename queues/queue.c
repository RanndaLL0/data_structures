#include "queue.h"


void *peek(struct queue *queue);
void push(struct queue *queue, void *data, unsigned long data_size);
void pop(struct queue *queue);


struct queue queue_constructor() {
        
        struct queue queue;

        queue.linked_list = linked_list_constructor();

        queue.peek = peek;
        queue.pop = pop;
        queue.push = push;

        return queue;
}

void queue_destructor(struct queue *queue) {
        linked_list_destructor(&queue->linked_list);
}

void push(struct queue *queue, void *data, unsigned long data_size) {
        queue->linked_list.insert(
                &queue->linked_list,
                queue->linked_list.length, 
                data, 
                data_size
        );
}

void pop(struct queue *queue) {
       queue->linked_list.remove(&queue->linked_list, 0); 
}

void *peek(struct queue *queue) {
        void *data = queue->linked_list.retrieve(&queue->linked_list, 0);

        return data;
}
