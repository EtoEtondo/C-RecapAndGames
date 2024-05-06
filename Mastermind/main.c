#include <stdio.h>
#include "mastermind.h"

int main() {
    printf("   -> Mastermind <-\n");
    mastermind_ctx_t ctx;
    mn_reset(&ctx);
    mn_print(&ctx);
    return 0;
}

