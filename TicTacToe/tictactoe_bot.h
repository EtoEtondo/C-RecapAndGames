#pragma once
#include <stdbool.h>
#include "tictactoe.h"

bool ttt_bot_win(ttt_ctx_t *ctx);

bool ttt_bot_rescue(ttt_ctx_t *ctx);

void nextTurn(ttt_ctx_t *ctx);
