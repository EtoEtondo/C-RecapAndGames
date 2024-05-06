#include <stdio.h>
#include <stdlib.h>

char * readline(const char *msg) {
    printf("%s: ",msg);
    char *input = NULL;
    size_t len = 0;
    getline(&input,&len,stdin);
    return input;
}


int main() {
    printf("--Notendurchschnitt-Rechner--\n");
    char* eingabe;
    char* eingabe2;
    float note;
    float anz = 0.0;
    float noten = 0.0;
    float durchschnitt;
    
    while(1){
        eingabe = readline("Möchten Sie eine weitere Note eingeben? j/n");
            if(eingabe[0] == 'j'){
                eingabe2 = readline("Bitte geben Sie Ihre Note ein");
                note = atoi(eingabe2);
                
                    if(note < 1 || note > 6){
                        printf("Nur Noten von 1 bis 6\n");
                        break;
                    }
                
                noten = noten + note;
                anz++;
                
            }else if (eingabe[0] == 'n'){
                durchschnitt = noten/anz;
                printf("--> Ihr Notendurchschnitt ist: %.3f\n", durchschnitt);
                break;
            }
    }
    
    return 0;
}
