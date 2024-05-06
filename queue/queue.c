#include "queue.h"
#include <stdlib.h>

int empty(queue_t *q){
    if(q==NULL || q->head==NULL) return 0;
    else return -1;
}

void* dequeue(queue_t *q){
    if(q==NULL || q->head==NULL) return NULL;
    qnode *node = q->head;
    void* data = node->data;
    q->head = node->next;
    if(q->head == NULL) q->tail=NULL;
    free(node);
    return data;
}

int enqueue(queue_t *q, void* data){
    if(q==NULL) return -1;
    
    if(q->tail == NULL){
        qnode *node= malloc(sizeof(*node));
        if(node==NULL) return -1;
        node->data = data;
        node->next = NULL;
        q->tail=node;
    }
    return 0;
}

queue_t *queue_new(void){
    queue_t *q = malloc(sizeof(*q));
    if (q==NULL) return NULL;
    q->head=q->tail=NULL;
    return q;
}

int queue_free(queue_t *q){
    if(q == NULL) return -1;

    while(q->head != NULL){
        qnode *node = q->head;
        q->head = node->next;
        free(node);
    }
    free(q);
    return 0;
}
