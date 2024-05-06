#pragma once

typedef struct stack{
    struct stack *ptr;
    void* data;
}stack;

void push();

int pop();


