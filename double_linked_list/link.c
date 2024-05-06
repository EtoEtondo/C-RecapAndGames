#include "link.h"
#include <stdio.h>
#include <stdlib.h>


lnode *new_list(void){
    lnode *new = (lnode*) malloc(sizeof(lnode));
    new->data =(void *) -1;
    new->right=NULL;
    new->left=NULL;
    return new;
}

lnode *insert(lnode *list, void* data){
    lnode *new = (lnode*) malloc(sizeof(lnode));
    new->data=data;
    new->left=list;
    new->right=NULL;
    list->right=new;
    new->right->left=NULL;
    return new;
}

lnode *delete(lnode *list);

void print_all(lnode *list);
