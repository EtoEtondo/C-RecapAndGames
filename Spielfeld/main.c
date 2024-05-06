#include <stdio.h>
#include <stdlib.h>

// Ausgabe Spielfeld
void printField(int *field) {
    printf("\n");
    int i, j;
    // Schleife fuer Zeilen, Y-Achse
    for(i=0; i<8; i++) {
        // Schleife fuer Spalten, X-Achse
        for(j=0; j<8; j++) {
            printf("%d ", *(field+i*8+j));
        }
        printf("\n");
    }
}
void move_figure(int *field, int *posX, int *posY, char zug){
    // alte Position loeschen
    *(field + *posY * 8 + *posX) = 0;
    
    // neue Position bestimmen
    switch(zug) {
        case 'w': (*posY)--; break;
        case 'a': (*posX)--; break;
        case 's': (*posY)++; break;
        case 'd': (*posX)++; break;
    }
    
    // Grenzueberschreitung pruefen
    if(*posX < 0) *posX = 7;
    if(*posX > 7) *posX = 0;
    if(*posY < 0) *posY = 7;
    if(*posY > 7) *posY = 0;
    
    // neue Position setzen
    *(field + *posY * 8 + *posX) = 1;
}

int main() {
    printf("Bewege die 1\n");
    int feld[8][8] = {0};
    int posX = 0, posY= 0;
    char zug;
    
    feld[0][0]= 1;
    
    do {
        printField(&feld[0][0]);
        printf("\nZug [w hoch, a links, s runter, d rechts, x beenden]: ");
        scanf("%c", &zug);
        move_figure(&feld[0][0], &posX, &posY, zug);
    } while (zug != 'x');
    
    return 0;
}
