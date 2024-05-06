#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "ttt.h"

void initialize(ttt_ctx_t* ctx){
   for(int row=0; row<BOARD_SIZE; row++){
      for(int col=0; col<BOARD_SIZE; col++){
         ctx->board[row][col] = EMPTY_CELL;
      }
   }
   ctx->currentplayer = PLAYER_ONE;
   ctx->bot = EMPTY_CELL;
}

void ttt_print_board(ttt_ctx_t* ctx){
   printf("    0   1   2  \n");
   printf("  -------------\n");
   for(int row=0; row<BOARD_SIZE; row++){
      printf("%d ", row);
      for(int col=0; col<BOARD_SIZE; col++){
         printf("| %c ", ctx->board[row][col]);
         if(col==2) printf("|\n");
      }
      printf("  -------------\n");
   }
}

bool ttt_full_board(ttt_ctx_t* ctx){
   for(int row=0; row<BOARD_SIZE; row++){
      for(int col=0; col<BOARD_SIZE; col++){
         if(ctx->board[row][col] == EMPTY_CELL)
            return false;
      }
   }
   return true;
}

bool ttt_empty_board(ttt_ctx_t* ctx){
   for(int row=0; row<BOARD_SIZE; row++){
      for(int col=0; col<BOARD_SIZE; col++){
         if(ctx->board[row][col] != EMPTY_CELL)
            return false;
      }
   }
   return true;
}

bool ttt_check_for_win(ttt_ctx_t* ctx){
   ttt_entry_t sym = ctx->currentplayer;
   ttt_entry_t bot = ctx->bot;
   int row, col;
   int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0;
    
   for(row = 0; row < BOARD_SIZE; row++) {
      for(col = 0; col < BOARD_SIZE; col++) {
         if(ctx->board[col][row] == sym) a++; //3 in einer Spalte Player
         if(ctx->board[col][row] == bot && bot != EMPTY_CELL) e++; //3 in einer Spalte Bot
         if(ctx->board[row][col] == sym) b++; //3 in einer Zeile Player
         if(ctx->board[row][col] == bot && bot != EMPTY_CELL) f++; //3 in einer Zeile Bot
      }
      if(a == 3 || b == 3){ //Zurücksetzen damit der nicht in verschiedenen Spalten/Zeilen counter hochzählt
         printf("Player %c. Congratulations! You won. :)\n", ctx->currentplayer);
         return true;
      }
      else{
         a=0;
         b=0;
      }
      if(e == 3 || f == 3){ //Zurücksetzen damit der nicht in verschiedenen Spalten/Zeilen counter hochzählt
         printf("Player %c. You lose. :(\n", ctx->currentplayer);
         return true;
      }
      else{
         e=0;
         f=0;
      }

      if(ctx->board[row][row] == sym) c++; //3 Diagonale oben links nach unten rechts Player
      if(ctx->board[row][BOARD_SIZE-row-1] == sym) d++; //3 Diagonale unten links nach oben rechts Player
    
      if(ctx->board[row][row] == bot && bot != EMPTY_CELL) g++; //3 Diagonale oben links nach unten rechts Bot
      if(ctx->board[row][BOARD_SIZE-row-1] == bot && bot != EMPTY_CELL) h++; //3 Diagonale unten links nach oben rechts Bot
   }

   if(c == 3 || d == 3){ 
      printf("Player %c. Congratulations! You won. :)\n", ctx->currentplayer);
      return true;
   }
   else if(g == 3 || h == 3){
      printf("Player %c. You lose. :(\n", ctx->currentplayer);
      return true;
   }
   else return false;
}

void ttt_switch_current_player(ttt_ctx_t* ctx){
   if(ctx->currentplayer == PLAYER_ONE && ctx->bot == EMPTY_CELL) ctx->currentplayer = PLAYER_TWO;
   else if(ctx->currentplayer == PLAYER_TWO && ctx->bot == EMPTY_CELL) ctx->currentplayer = PLAYER_ONE;
}

bool ttt_place_mark(ttt_ctx_t* ctx, int row, int col, ttt_entry_t val){
   if(row < 0 || row > 2 || col < 0 || col > 2)
      return false;
   if(ctx->board[row][col] == EMPTY_CELL){
      ctx->board[row][col] = val;
      return true;
   }
   return false;
}
