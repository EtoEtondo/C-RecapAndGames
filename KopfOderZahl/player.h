#pragma once
#include <stdbool.h>
#include "coin.h"

typedef struct player{
    char * name;
    int balance;
    enum coin wahl;
}player_t;

void withdraw(player_t *p, int amount);
void deposit(player_t *p, int amount);
bool broke(player_t *p);

