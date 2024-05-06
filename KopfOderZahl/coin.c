#include "coin.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

static bool INIT=false;

enum coin toss(void){
    if(INIT==false){
        INIT=true;
        srand((int)time(NULL)+(int)getpid());
    }
    return rand()%2;
}
