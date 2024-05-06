#include "mastermind.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static bool elephant=false;

void mn_random(mastermind_ctx_t ctx){
    if(!elephant){
        srand((int)time(NULL)+(int)getpid());
        elephant=true;
    }
    for(int i=0; i<4; i++){
        int giraffe=rand()%6;
        switch (giraffe) {
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
            case 5: break;
            default: break;
        }
    }
}

bool is_color(char* c){
    for(int i=0; i<ROW_SIZE;i++){
        switch (c[i]) {
            case 'r': return true;
                break;
            case 'y': return true;
                break;
            case 'g': return true;
                break;
            case 'v': return true;
                break;
            case 'o': return true;
                break;
            case 'p': return true;
                break;
            default: return false;
                break;
        }
    }
    return false;
}

char * readline(const char *msg) {
    printf("%s: ",msg);
    char *input = NULL;
    size_t len = 0;
    getline(&input,&len,stdin);
    return input;
}

void mn_reset(mastermind_ctx_t *ctx){
    memset(ctx->board,EMPTY_CELL,MAX_GUESSES*ROW_SIZE*sizeof(char));
    memset(ctx->code,EMPTY_CELL,ROW_SIZE*sizeof(char));
    ctx->turn=0;
}

bool mn_won(mastermind_ctx_t *ctx){
    int count=0;
    for(int i = 0; i<ROW_SIZE; i++){
        if(ctx->code[i]==ctx->board[ctx->turn][i]){
            count++;
        }
    }return count==ROW_SIZE;
}

bool mn_time_up(mastermind_ctx_t *ctx){
    return ctx->turn==MAX_GUESSES;
}

bool mn_game_over(mastermind_ctx_t *ctx){
    if(mn_time_up(ctx)){
      printf("Sie haben keine Züge mehr.. Leider verloren :(\n");
        return true;
    }else if(mn_won(ctx)){
        printf("Herzlichen Glückwunsch! Sie haben den Code geknackt ;D\n");
        return true;
    }
    return false;
}

bool mn_guess(mastermind_ctx_t *ctx){
    for(int i=0; i<ROW_SIZE;i++){
        printf("Geben Sie Ihre %d. Vermutung ein", i);
        char* c = readline("");
        if(!is_color(c)){
            free(c);
            return false;
        }
        ctx->board[ctx->turn][i]=c[0];
        free(c);
    }
    return true;
}

void mn_print(mastermind_ctx_t *ctx){
    printf(" RED:'r'\n GREEN:'g'\n YELLOW:'y'\n ORANGE:'o'\n PINK:'p'\n VIOLETT:'v'\n\n\n");
    for(int i=0; i<MAX_GUESSES; i++){
        printf("   -----------------\n");
        printf("%2d ", i+1);
        for(int j=0; j<ROW_SIZE; j++){
            printf("| %c ", ctx->board[i][j]);
        }
        printf("|");
        mn_print_pegs(ctx);
    }
    printf("   -----------------\n");
}

void mn_print_pegs(mastermind_ctx_t *ctx){
    int cw=0, cb=0;
    for(int i=0; i<ROW_SIZE; i++){
        if(ctx->board[ctx->turn][i] == ctx->code[i]){
            cb++;
            continue;
        }
        for(int j=0;j<ROW_SIZE;j++){
            if(ctx->board[ctx->turn][i] == ctx->code[j]) {
                cw++;
            }
        }
    }
    for(int k=0; k<cb; k++) printf("%2s", "b");
    for(int l=0; l<cw; l++) printf("%2s", "w");
    printf("\n");
}


