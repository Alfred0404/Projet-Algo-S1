#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct {
    int joueur, tresor, orientation;
    char type;
}Tuile;

Tuile** creer_plateau() {
    Tuile **plateau = malloc(7 * sizeof(Tuile*));
    for (int i = 0; i < 7; i++) {
        plateau[i] = malloc(7 * sizeof(Tuile));
    }
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (i == 0 && j == 0) {
                plateau[i][j].type = 'c';
                plateau[i][j].joueur = 1;
                plateau[i][j].tresor = 0;
                plateau[i][j].orientation = 0;
            }
            else if (i == 0 && j == 6) {
                plateau[i][j].type = 'c';
                plateau[i][j].joueur = 2;
                plateau[i][j].tresor = 0;
                plateau[i][j].orientation = 1;
            }
            else if (i == 6 && j == 0) {
                plateau[i][j].type = 'c';
                plateau[i][j].joueur = 3;
                plateau[i][j].tresor = 0;
                plateau[i][j].orientation = 2;
            }
            else if (i == 6 && j == 6) {
                plateau[i][j].type = 'c';
                plateau[i][j].joueur = 4;
                plateau[i][j].tresor = 0;
                plateau[i][j].orientation = 3;
            }
            else {
                plateau[i][j].type = 't';
                plateau[i][j].joueur = 0;
                plateau[i][j].tresor = 1;
                plateau[i][j].orientation = rand() % 4;
            }
        }
    }
    return plateau;
}

void afficher_plateau(Tuile **plateau) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            printf("%c%c%c  ", 0xDB, 0xDB, 0xDB);
            printf("%c      ", 0xDB);
            printf("%c  %c  ", 0xDB, 0xDB);
        }
    }
    printf("\n");
}

int main() {
    //Tuile **plateau = creer_plateau();
    //afficher_plateau(plateau);
    printf("%c%c%c \n", 0xDB, 0xDB, 0xDB);
    printf("%c     \n", 0xDB);
    printf("%c %c \n", 0xDB, 0xDB);
    return 0;
}