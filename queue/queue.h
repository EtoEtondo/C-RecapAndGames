#pragma once

typedef struct node {
    void* data;
    struct node *next;
}qnode;

typedef struct queue {
    struct node *head;
    struct node *tail;
    unsigned int size;
}queue_t;

int empty(queue_t *q);

void* dequeue(queue_t *q);

int enqueue(queue_t *q, void* data);

queue_t *queue_new(void);

int queue_free(queue_t *q);
