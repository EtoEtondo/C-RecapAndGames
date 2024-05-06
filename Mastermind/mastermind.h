#pragma once

#include <stdbool.h>

#define ROW_SIZE 4
#define COLORS 6
#define MAX_GUESSES 12
#define EMPTY_CELL '-'
#define red 'r'
#define green 'g'
#define yellow 'y'
#define violett 'v'
#define orange 'o'
#define black 'b'
#define white 'w'
#define pink 'p'

typedef struct mastermind_ctx{
    char code[ROW_SIZE];
    char board[MAX_GUESSES][ROW_SIZE];
    unsigned int turn;
}mastermind_ctx_t;

void mn_reset(mastermind_ctx_t *ctx);

bool mn_won(mastermind_ctx_t *ctx);

bool mn_time_up(mastermind_ctx_t *ctx);

bool mn_game_over(mastermind_ctx_t *ctx);

bool mn_guess(mastermind_ctx_t *ctx);

void mn_print(mastermind_ctx_t *ctx);

void mn_print_pegs(mastermind_ctx_t *ctx);
