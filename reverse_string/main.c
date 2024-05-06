#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* a="Hallo Welt!";
    char b[(int)strlen(a)];
    int j=0;
    
    for(int i = (int)strlen(a)-1; i >= 0; i--){
            b[j]=a[i];
            j++;
    }
    
    printf("%d\n", (int)strlen(a));
    printf("String: %s\n",a);
    printf("Reverse String: %s\n",b);
    
    return 0;
}


//  0 = !
