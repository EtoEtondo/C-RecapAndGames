#pragma once
#include <stdbool.h>

#define BOARD_SIZE 3

typedef enum ttt_entry{PLAYER_ONE = 'X', PLAYER_TWO = 'O', EMPTY_CELL = ' '} ttt_entry_t;

typedef struct ttt_ctx{
   char board[BOARD_SIZE][BOARD_SIZE];
   ttt_entry_t currentplayer;
   ttt_entry_t bot; // EMPTY_CELL == PVP-Mode
}ttt_ctx_t;

void initialize(ttt_ctx_t* ctx);

void ttt_print_board(ttt_ctx_t* ctx);

bool ttt_full_board(ttt_ctx_t* ctx);

bool ttt_empty_board(ttt_ctx_t* ctx);

bool ttt_check_for_win(ttt_ctx_t* ctx);

void ttt_switch_current_player(ttt_ctx_t* ctx);

bool ttt_place_mark(ttt_ctx_t* ctx, int row, int col, ttt_entry_t val);
