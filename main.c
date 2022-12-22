#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#define TRUE 1
#define FALSE 0
#define HEIGHT 7
#define WIDTH 7

void Color(int CouleurTexte, int couleurFond) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurFond * 16 + CouleurTexte);
}

typedef struct {
    int joueur, tresor, orientation;
    char type;
}Tuile;

void debut_partie() {
    int nb_joueur;
    printf("~~~~~~ ! NOUVELLE PARTIE ! ~~~~~~ \n");
    do {
        printf("Choisissez le nombre de joueur : \n");
        scanf("%d", &nb_joueur);
    } while (nb_joueur < 2 || nb_joueur > 4);
    printf("Vous avez choisi %d joueurs \n", nb_joueur);
}

void remplir_plateau(Tuile plateau[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 && j == 0 || i == 0 && j == HEIGHT - 1 || i == WIDTH - 1 && j == 0 || i == WIDTH - 1 && j == HEIGHT - 1) {
                Color(0, 15);
                plateau[i][j].type = 'L';
                plateau[i][j].tresor = 0;
            }
            else if (i % 2 == 0 && j % 2 == 0) {
                plateau[i][j].type = 'T';
                plateau[i][j].tresor = 0;
            }
            else {
                plateau[i][j].type = '.';
                plateau[i][j].tresor = 0;
            }
        }
    }
}

void afficher_plateau_debug(Tuile plateau[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (plateau[i][j].type == 'L') {
                Color(12, 0);
                printf("%c ", plateau[i][j].type);
            }
            else if (plateau[i][j].type == 'T') {
                Color(9, 0);
                printf("%c ", plateau[i][j].type);
            }
            else {
                Color(0, 0);
                printf("%c ", plateau[i][j].type);
            }
        }
        Color(15, 0);
        printf("\n");
    }
}

int main() {

    Tuile plateau[HEIGHT][WIDTH];
    remplir_plateau(plateau);
    afficher_plateau_debug(plateau);
    
    return 0;
}