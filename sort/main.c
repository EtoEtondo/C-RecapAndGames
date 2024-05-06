#include <stdio.h>
#include <stdlib.h>

int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}


int main() {
    int a[7] = {1, 4, 3, -2, 29, -12, 145};
    int hold;
    
    printf("Array sortieren...\n");
    
    for(int j=1; j<7;j++){
        for(int i=0; i<7-j;i++){
            if(a[i]>a[i+1]){
                    hold=a[i+1];
                    a[i+1]=a[i];
                    a[i]=hold;
            }
        }
    }
    
    for(int z=0; z<7;z++){
        printf("a sortiert: %d\n",a[z]);
    }
    
//----------------------------------------
    printf("qsort..\n");
    int b[4]={2,9,-3,1};
    int size= sizeof(b)/sizeof(*b);
    
    qsort(&b[0], size,sizeof(int), cmpfunc);
    
    for(int t=0; t<4;t++){
        printf("b sortiert: %d\n",b[t]);
    }
    return 0;
}


