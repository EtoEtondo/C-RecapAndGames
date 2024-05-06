#include <stdio.h>
#include "coin.h"
#include "player.h"
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

char * readline(const char *msg) {
    printf("%s: ",msg);
    char *input = NULL;
    size_t len = 0;
    getline(&input,&len,stdin);
    return input;
}

int auszahlung(int gs, int wett){
    switch (gs) {
        case 1: wett = wett*1; break;
        case 2: wett = wett*5; break;
        case 3: wett = wett*7; break;
        default: wett = 0; break;
    }
    return wett;
}


void two_up(player_t *p){
    int gs = 0, odds = 0;
    int wetteinstatz = atoi(readline("Wetteinsatz"));
    p->balance = p->balance-wetteinstatz;
    p->wahl= atoi(readline("Wähle [Kopf=0] oder [Zahl=1]"));
    if(p->wahl==0) printf("Sie haben Kopf gewählt\n");
    else printf("Sie haben Zahl gewählt\n");
    while(1){
        int erg1 = toss();
        int erg2 = toss();
        printf("%c, %c\n", erg1 ? 'Z' : 'K', erg2 ? 'Z' : 'K');
        
        if(p->wahl != erg1 && p->wahl != erg2){
            break;
        }else if(erg1 != erg2){
            odds++;
            if(odds >= 5){
                break;
            }
        }else{
            gs++;
            if(gs>=3){
                break;
            }
        }
        sleep(1);
    }
    p->balance += auszahlung(gs, wetteinstatz);
}



int main() {
    printf("--> Two Up <--\n");
    player_t p1;
    int spielen;
    p1.balance = atoi(readline("Ihr Guthaben"));
    while(1){
        if(p1.balance<=0){
            printf("Sie haben kein Guthaben mehr\n");
            break;
        }
        sleep(1);
        printf("Ihr Aktuelles Guthaben: %d\n", p1.balance);
        spielen=atoi(readline("Wähle [0 = spielen] oder [1 = beenden]"));
        if(spielen==0) two_up(&p1);
        else break;
    }
    printf("Sie haben jetzt %d Euro\n", p1.balance);
    
    return 0;
}
