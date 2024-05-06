#include <unistd.h>
#include <stdio.h>
#include "tictactoe.h"
#include <stdlib.h>
#include <stdbool.h>
#include "tictactoe_bot.h"

char * readline(const char *msg) {
    printf("%s: ",msg);
    char *input = NULL;
    size_t len = 0;
    getline(&input,&len,stdin);
    return input;
}


void play(ttt_ctx_t *ctx){
    int wahl;
    char* j;
    do{
        wahl = atoi(readline("[1] Spieler vs Bot | [2] Spieler vs Spieler"));
    }while(wahl>2 || wahl<0);
    
    if(wahl==1){
            j = readline("Wollen Sie als erster anfangen? j/n");
                if(j[0]=='j'){
                    ctx->bot=PLAYER_TWO;
                }else{
                    ctx->bot=PLAYER_ONE;
                }
        }

    int row,col;
    bool truethnis;
    
    while(1){
    do{
        if(ctx->currentplayer== PLAYER_ONE){
            row= atoi(readline("Spieler X Ihre Zeilennummer"));
            col= atoi(readline("Spieler X Ihre Spaltennummer"));
        }else{
            row= atoi(readline("Spieler O Ihre Zeilennummer"));
            col= atoi(readline("Spieler O Ihre Spaltennummer"));
        }
        truethnis = ttt_place_mark(ctx, row, col);
    }while(row>2 || row<0 || col>2 || col<0 || !truethnis);
    
    printf("\n\n");
    ttt_print_board(ctx);
    
        if(ttt_check_for_win(ctx)){
            printf("Spieler %c. ggwp, hast gewonnen! :D\n\n",ctx->currentplayer);
            break;
        }else if(ttt_full_board(ctx)){
            printf("Unentschieden! Probiert es nochmal :D\n");
            break;
        }
    
    ttt_switch_current_player(ctx);
    }
}
    
   
int main(){
    
    char* ant;
    
    do{
        sleep(1);
        printf("Tic Tac Toe\n");
        ttt_ctx_t ctx;
        ttt_initialize(&ctx);
        ttt_print_board(&ctx);
        ant = readline("Möchten Sie spielen j/n");
        if(ant[0] == 'j') play(&ctx);
        else if(ant[0] == 'n') break;
    }while(ant[0]!='j' || ant[0]!='n');
    return 0;
}
