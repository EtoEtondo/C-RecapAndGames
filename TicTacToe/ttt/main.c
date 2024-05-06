#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "ttt.h"
#include "ttt_bot.h"

static int r;

char* readline(const char* msg){
   printf("%s", msg);
   char* in = NULL;
   size_t len = 0;
   getline(&in, &len, stdin);
   return in;
}


void mark(ttt_ctx_t* ctx){
   char* coord;
   bool erfolg = false;
   int row, col;
   do{
      if(r == 0){
         if(ctx->currentplayer == PLAYER_ONE)
            coord = readline("Player X enter your coordinates (row col): ");
         else if(ctx->currentplayer == PLAYER_TWO)
            coord = readline("Player O enter your coordinates (row col): ");
         
         row = *(coord+0)-'0';
         col = *(coord+2)-'0';
         if((erfolg = ttt_place_mark(ctx, row, col, ctx->currentplayer)) && ctx->bot != EMPTY_CELL)
            r++;
      }else{
         sleep(1);
         nextTurn(ctx);
         r--;
         break;
      }
   }while(row < 0 || row > 2 || col < 0 || col > 2 || !erfolg);
}


void play(ttt_ctx_t* ctx){
   char* m = " ";
   char* z = " ";
   do{
      m = readline("[1] PvE oder [2] PvP: ");
   }while(*(m+0) != '1' && m[0] != '2');
   
   if(m[0] == '1'){
      do{
         z = readline("Wollen Sie als erster anfangen: Ja[1] Nein[0]: ");
      }while(z[0] != '1' && z[0] != '0');
   
      if(z[0] == '1'){
         ctx->currentplayer = PLAYER_ONE;
         ctx->bot = PLAYER_TWO;
      }else if(z[0] == '0'){
         ctx->currentplayer = PLAYER_TWO;
         ctx->bot = PLAYER_ONE;
         r++;
      }
   }

   while(1){
      mark(ctx);

      printf("\n\n");
      ttt_print_board(ctx);
      
      if(ttt_check_for_win(ctx)){
         break;
      }else if(ttt_full_board(ctx)){
         printf("Unentschieden!\n");
         break;
      }
      ttt_switch_current_player(ctx);
   }
}



int main(){
   char* again;
   do{
      r = 0;
      ttt_ctx_t ctx;
      initialize(&ctx);
      ttt_print_board(&ctx);
      
      play(&ctx);

      again = readline("Wollen Sie erneut spielen? Ja[1] Nein[0]: ");
      printf("\n\n");
   }while(again[0] == '1');
   return 0;
}
