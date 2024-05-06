#include <stdio.h>
#include <stdlib.h>

void println(int anz){
    if(anz>=3){
        printf("Counter: %d\n",anz);
        println(anz-1);
    }
}

int main(){
    int z;
    scanf("%d",&z);
    printf("Counter auf %d gesetzt\n", z);
    println(z);
    return 0;
}

