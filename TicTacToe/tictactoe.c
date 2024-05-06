#include "tictactoe.h"
#include <stdio.h>
#include <stdlib.h>

void ttt_initialize(ttt_ctx_t *ctx){
    for(int row=0; row<BOARD_SIZE;row++){
        for(int col=0;col<BOARD_SIZE;col++){
            ctx->board[row][col] = EMPTY_CELL;
        }
    }
    ctx->currentplayer=PLAYER_ONE;
    ctx->bot=EMPTY_CELL;
}

void ttt_print_board(ttt_ctx_t *ctx){
    printf("-------------\n");
    for(int row=0; row<BOARD_SIZE;row++){
        for(int col=0;col<BOARD_SIZE;col++){
            printf("| %c ", ctx->board[row][col]);
            if(col==2) {printf("|\n"); printf("-------------\n");}
        }
    }
}

bool ttt_full_board(ttt_ctx_t *ctx){
    for(int row=0; row<BOARD_SIZE;row++){
        for(int col=0;col<BOARD_SIZE;col++){
            if(ctx->board[row][col] == EMPTY_CELL) return false;
        }
    }
    return true;
}

bool ttt_empty_board(ttt_ctx_t *ctx){
    for(int row=0; row<BOARD_SIZE;row++){
        for(int col=0;col<BOARD_SIZE;col++){
            if(ctx->board[row][col] != EMPTY_CELL) return false;
        }
    }
    return true;
}

bool ttt_check_for_win(struct ttt_ctx *ctx) {
    
    enum ttt_entry sym = ctx->currentplayer;
    int i, j;
    int a = 0, b = 0, c = 0, d = 0;
    
    for(i = 0; i < BOARD_SIZE; i++) {
        for(j = 0; j < BOARD_SIZE; j++) {
            if(ctx->board[j][i] == sym) a++;    //Reihe durchgehen
            if(ctx->board[i][j] == sym) b++;    //Zeile durchgehen
        }
        if(a==3 || b ==3) break;    //schon gewonnen abbrechen
        else{a=0;b=0;}              //falls nicht gewonnen zurücksetzen
            
        if(ctx->board[i][i] == sym) c++;    //Diagonale durchgehen
        if(ctx->board[i][BOARD_SIZE-i-1] == sym) d++;
    }
    
    if(a == 3 || b == 3 || c == 3 || d == 3) return true;
    else return false;
    
}

void ttt_switch_current_player(ttt_ctx_t *ctx){
    if(ctx->currentplayer == PLAYER_ONE && ctx->bot==EMPTY_CELL) ctx->currentplayer = PLAYER_TWO;
    else if(ctx->currentplayer == PLAYER_TWO && ctx->bot==EMPTY_CELL) ctx->currentplayer = PLAYER_ONE;
}

bool ttt_place_mark (ttt_ctx_t *ctx, int row, int col){
    if(row>2 || row<0 || col>2 || col<0) return false;
    if(ctx->board[row][col]==EMPTY_CELL){
        ctx->board[row][col]=ctx->currentplayer;
        return true;
    }
    return false;
}
