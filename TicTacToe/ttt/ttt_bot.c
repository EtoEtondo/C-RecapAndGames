#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "ttt_bot.h"

static bool rando=false;

bool ttt_bot_win_row(ttt_ctx_t *ctx, int row) {
   int counts=0;
   for(int i=0; i<BOARD_SIZE; i++)
      if(ctx->board[row][i] == ctx->bot) counts+=1;
      else if(ctx->board[row][i] != EMPTY_CELL) counts-=1;
      
   return counts==2;
}



bool ttt_bot_win_column(ttt_ctx_t *ctx, int col) {
   int counts=0;
   for(int i=0; i<BOARD_SIZE; i++)
      if(ctx->board[i][col] == ctx->bot) counts+=1;
      else if(ctx->board[i][col] != EMPTY_CELL) counts-=1;
      
   return counts==2;
}



bool ttt_bot_win_diaLR(ttt_ctx_t* ctx){
   int counts=0;
   for(int i=0; i<BOARD_SIZE; i++){
      if(ctx->board[i][i] == ctx->bot) counts++;
      else if(ctx->board[i][i] != EMPTY_CELL) counts--;
   }
   return counts==2;
}



bool ttt_bot_win_diaRL(ttt_ctx_t* ctx){
   int counts=0;
   for(int i=0; i<BOARD_SIZE; i++){
      if(ctx->board[BOARD_SIZE-i-1][i] == ctx->bot) counts++;
      else if(ctx->board[BOARD_SIZE-i-1][i] != EMPTY_CELL) counts--;
   }
   return counts==2;
}


bool ttt_bot_win(ttt_ctx_t* ctx){
   for(int i=0;i<BOARD_SIZE;i++){ 
      if(ttt_bot_win_row(ctx,i)){
         for(int j=0; j<BOARD_SIZE; j++)
            if(ttt_place_mark(ctx,i,j, ctx->bot)) return true;
      }
      
      if(ttt_bot_win_column(ctx,i)) {
         for(int j=0; j<BOARD_SIZE; j++)
            if(ttt_place_mark(ctx,j,i, ctx->bot)) return true;
      }
    
      if(ttt_bot_win_diaLR(ctx)){
         for(int j=0; j<BOARD_SIZE; j++)
            if(ttt_place_mark(ctx, j, j, ctx->bot)) return true;
      }

      if(ttt_bot_win_diaRL(ctx)){
         for(int j=0; j<BOARD_SIZE; j++)
            if(ttt_place_mark(ctx, j, BOARD_SIZE-j-1, ctx->bot)) return true;
      }
   }
}

bool ttt_bot_rescue_row(ttt_ctx_t *ctx, int row){
   int counts=0;
   for(int i=0; i<BOARD_SIZE; i++)
      if(ctx->board[row][i] == ctx->currentplayer) counts+=1;
      else if(ctx->board[row][i] != EMPTY_CELL) counts-=1;

   return counts==2;
}



bool ttt_bot_rescue_column(ttt_ctx_t *ctx, int col) {
   int counts=0;
   for(int i=0; i<BOARD_SIZE; i++)
      if(ctx->board[i][col] == ctx->currentplayer) counts+=1;
      else if(ctx->board[i][col] != EMPTY_CELL) counts-=1;
      
   return counts==2;
}



bool ttt_bot_rescue_diaLR(ttt_ctx_t* ctx){
   int counts=0;
   for(int i=0; i<BOARD_SIZE; i++){
      if(ctx->board[i][i] == ctx->currentplayer) counts++;
      else if(ctx->board[i][i] != EMPTY_CELL) counts--;
   }
   return counts==2;
}



bool ttt_bot_rescue_diaRL(ttt_ctx_t* ctx){
   int counts=0;
   for(int i=0; i<BOARD_SIZE; i++){
      if(ctx->board[i][BOARD_SIZE-i-1] == ctx->currentplayer) counts++;
      else if(ctx->board[i][BOARD_SIZE-i-1] != EMPTY_CELL) counts--;
   }
   return counts==2;
}


bool ttt_bot_rescue(ttt_ctx_t* ctx){
   for(int i=0;i<BOARD_SIZE;i++){ 
      if(ttt_bot_rescue_row(ctx,i)){
         for(int j=0; j<BOARD_SIZE; j++)
            if(ttt_place_mark(ctx,i,j, ctx->bot)) return true;
      }
      
      if(ttt_bot_rescue_column(ctx,i)) {
         for(int j=0; j<BOARD_SIZE; j++)
            if(ttt_place_mark(ctx,j,i, ctx->bot)) return true;
      }
    
      if(ttt_bot_rescue_diaLR(ctx)){
         for(int j=0; j<BOARD_SIZE; j++)
            if(ttt_place_mark(ctx, j, j, ctx->bot)) return true;
      }
   
      if(ttt_bot_rescue_diaRL(ctx)){
         for(int j=0; j<BOARD_SIZE; j++)
            if(ttt_place_mark(ctx, BOARD_SIZE-j-1, j, ctx->bot)) return true;
      }
   }
}


void nextTurn(ttt_ctx_t* ctx){
   if(!rando){
      srand(time(NULL)+getpid());
      rando = true;
   }
   
   
   if(ttt_bot_win(ctx)) return;
   if(ttt_bot_rescue(ctx)) return;
      
   int c = rand()%4;

   if(ttt_place_mark(ctx, 1, 1, ctx->bot)) return;
   switch(c){
      case 3: if(ttt_place_mark(ctx, 0, 2, ctx->bot)) return;
      case 2: if(ttt_place_mark(ctx, 2, 0, ctx->bot)) return;
      case 1: if(ttt_place_mark(ctx, 2, 2, ctx->bot)) return;
      case 0: if(ttt_place_mark(ctx, 0, 0, ctx->bot)) return;
      default:
         c = rand()%4;
         switch(c){
            case 3: if(ttt_place_mark(ctx, 0, 1, ctx->bot)) return;
            case 2: if(ttt_place_mark(ctx, 1, 0, ctx->bot)) return;
            case 1: if(ttt_place_mark(ctx, 1, 2, ctx->bot)) return;
            case 0: if(ttt_place_mark(ctx, 2, 1, ctx->bot)) return;
         }
   }
}
