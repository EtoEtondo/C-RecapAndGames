#include "player.h"

void withdraw(player_t *p, int amount){ //Geld vom verlierer abziehen
    p->balance = p->balance - amount;
}


void deposit(player_t *p, int amount){  //Geld dem Gewinner geben
    p->balance = p->balance + amount;
}


bool broke(player_t *p){
    return (p->balance<=0);
}


