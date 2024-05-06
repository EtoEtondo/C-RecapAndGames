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

bool verloren(player_t p){
    if(broke(&p)){
        printf("   ========== Game Over ==========\n");
        sleep(1);
        printf("Sie haben leider verloren :( %s", p.name);
        printf("Ihr neues Guthaben ist: %d\n",p.balance);
        return true;
    }
    return false;
}

void ergebnis(player_t *p1, player_t *p2, int wetteinstatz){
    printf("Der Gewinner ist %s", p1->name);
    deposit(p1, wetteinstatz);
    withdraw(p2, wetteinstatz);
    printf("Ihr neues Guthaben beträgt: %d\n", p1->balance);
    sleep(1);
    printf("\n");
}

int main() {
    player_t p1,p2;
    int wetteinsatz;
    int count = 1;
    
    p1.name = readline("Player 1 Name");
    p1.balance = atoi(readline("Player 1 Guthaben"));
    p2.name = readline("Player 2 Name");
    p2.balance = atoi(readline("Player 2 Guthaben"));
    printf("[Kopf=0] und [Zahl=1]\n");
    
    
    while(1){
        if(verloren(p1)) break;
        if(verloren(p2)) break;
        
        sleep(1);
        printf("\n   ========== Runde %d ============\n", count);
        printf("Spieler 1 (Guthaben in EUR, Name): %d, %s\n",p1.balance, p1.name);
        printf("Spieler 2 (Guthaben in EUR, Name): %d, %s\n",p2.balance, p2.name);
        wetteinsatz = atoi(readline("Wetteinsatz"));
        
        if(count%2){
            p1.wahl= atoi(readline("Spieler1 wählt [Kopf=0] oder [Zahl=1]"));
            if(p1.wahl==0){
                p2.wahl=1;
                printf("--> Spieler2 bekommt Zahl <--\n");
            }else{
                p2.wahl=0;
                printf("--> Spieler2 bekommt Kopf <--\n");
            }
            count++;
        }else{
            p2.wahl= atoi(readline("Spieler2 wählt [Kopf=0] oder [Zahl=1]"));
            if(p2.wahl==0){
                p1.wahl=1;
                printf("--> Spieler1 bekommt Zahl <--\n");
            }else{
                p1.wahl=0;
                printf("--> Spieler1 bekommt Kopf <--\n");
            }
            count++;
        }
        
        int erg=toss();
        if(p1.wahl==erg){
            ergebnis(&p1,&p2,wetteinsatz);
        }else{
            ergebnis(&p2,&p1, wetteinsatz);
        }
        
    }
    
    return 0;
}
