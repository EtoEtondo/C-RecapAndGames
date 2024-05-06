#include "tictactoe_bot.h"
#include <stdbool.h>
#include "tictactoe.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static bool rando = false;

bool ttt_bot_win(ttt_ctx_t *ctx){
    enum ttt_entry sym = ctx->bot;
    enum ttt_entry ply = ctx->currentplayer;
    int i, j;
    char coord[3][3]={'-'};
    int a = 0, b = 0, c = 0, d = 0;
    
    for(i = 0; i < BOARD_SIZE; i++) {
        for(j = 0; j < BOARD_SIZE; j++) {
            if(ctx->board[j][i] == sym) a++;    //Reihe durchgehen
            else if(ctx->board[j][i] == ply) a--;
            else coord[j][i] = EMPTY_CELL;
            
            if(ctx->board[i][j] == sym) b++;    //Zeile durchgehen
            else if (ctx->board[i][j] == ply) b--;
            else coord[i][j] = EMPTY_CELL;
        }
        if(a==2 || b ==2) break;    //schon gewonnen abbrechen
        else{a=0;b=0;}              //falls nicht gewonnen zurücksetzen
        
        if(ctx->board[i][i] == sym) c++;    //Diagonale durchgehen
        else if (ctx->board[i][i] == ply) c--;
        else coord[i][i] = EMPTY_CELL;
        
        if(ctx->board[i][BOARD_SIZE-i] == sym) d++;
        else if (ctx->board[i][BOARD_SIZE-i] == ply) d--;
        else coord[i][BOARD_SIZE-i] = EMPTY_CELL;
    }
    
    if(a == 2 || b == 2 || c == 2 || d == 2){
        for(i=0;i<BOARD_SIZE;i++){
            for(j=0;j<BOARD_SIZE;j++){
                if(coord[i][j]==EMPTY_CELL){
                    ttt_place_mark(ctx, i, j);
                    return ttt_check_for_win(ctx);
                }
            }
        }
    }
    return false;
}

bool ttt_bot_rescue(ttt_ctx_t *ctx){
    enum ttt_entry sym = ctx->currentplayer;
    enum ttt_entry ply = ctx->bot;
    int i, j;
    char coord[3][3]={'-'};
    int a = 0, b = 0, c = 0, d = 0;
    
    for(i = 0; i < BOARD_SIZE; i++) {
        for(j = 0; j < BOARD_SIZE; j++) {
            if(ctx->board[j][i] == sym) a++;    //Reihe durchgehen
            else if(ctx->board[j][i] == ply) a--;
            else coord[j][i] = EMPTY_CELL;
            
            if(ctx->board[i][j] == sym) b++;    //Zeile durchgehen
            else if (ctx->board[i][j] == ply) b--;
            else coord[i][j] = EMPTY_CELL;
        }
        if(a==2 || b ==2) break;    //schon gewonnen abbrechen
        else{a=0;b=0;}              //falls nicht gewonnen zurücksetzen
        
        if(ctx->board[i][i] == sym) c++;    //Diagonale durchgehen
        else if (ctx->board[i][i] == ply) c--;
        else coord[i][i] = EMPTY_CELL;
        
        if(ctx->board[i][BOARD_SIZE-i] == sym) d++;
        else if (ctx->board[i][BOARD_SIZE-i] == ply) d--;
        else coord[i][BOARD_SIZE-i] = EMPTY_CELL;
    }
    
    if(a == 2 || b == 2 || c == 2 || d == 2){
        for(i=0;i<BOARD_SIZE;i++){
            for(j=0;j<BOARD_SIZE;j++){
                if(coord[i][j]==EMPTY_CELL){
                    ttt_place_mark(ctx, i, j);
                    return ttt_check_for_win(ctx);
                }
            }
        }
    }
    return false;
}

void nextTurn(ttt_ctx_t* ctx){
    if(!rando){
        srand((int)time(NULL)+(int)getpid());
        rando = true;
    }
    
    
    if(ttt_bot_win(ctx)) return;
    if(ttt_bot_rescue(ctx)) return;
    
    int c = rand()%4;
    
    if(ttt_place_mark(ctx, 1, 1)) return;
    switch(c){
        case 3: if(ttt_place_mark(ctx, 0, 2)) return;
        case 2: if(ttt_place_mark(ctx, 2, 0)) return;
        case 1: if(ttt_place_mark(ctx, 2, 2)) return;
        case 0: if(ttt_place_mark(ctx, 0, 0)) return;
        default:
            c = rand()%4;
            switch(c){
                case 3: if(ttt_place_mark(ctx, 0, 1)) return;
                case 2: if(ttt_place_mark(ctx, 1, 0)) return;
                case 1: if(ttt_place_mark(ctx, 1, 2)) return;
                case 0: if(ttt_place_mark(ctx, 2, 1)) return;
            }
    }
}
