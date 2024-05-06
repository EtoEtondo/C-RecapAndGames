#pragma once

typedef struct node{
    struct node *left;
    struct node *right;
    void* data;
}lnode;

lnode *new_list(void);

lnode *insert(lnode *list, void*data);

lnode *delete(lnode *list);

void print_all(lnode *list);    //iterator
