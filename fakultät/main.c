#include <stdio.h>

int fakultät(int zahl){
    if(zahl>1){
        return zahl * fakultät(zahl-1);
    }else{
        return 1;
    }
}

int main() {
    printf("Fakultät berechnen:\n");
    int z;
    scanf("%d",&z);
    printf("Fakultät von %d! = %d\n", z, fakultät(z));
    return 0;
}
