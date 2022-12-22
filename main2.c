#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define H 7
#define L 7

void Color(int CouleurTexte, int couleurFond) { // changer couleur console
    HANDLE R = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(R, couleurFond * 16 + CouleurTexte);
}


int* remplir(int maze[H][L]) { // remplir plateau 7x7 aleatoirement
    srand(time(NULL));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < L; j++) {
            maze[i][j] = rand();
        }
    }
    return maze;
}


void afficher1(int maze[H][L]) { // afficher plateau 7x7 (normal)
    for (int i = 0; i < H; i++) {
        for(int j = 0; j < L; j++) {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


void afficher2(int maze[H][L], int maze_affichage[H*3][L*3]) { // afficher plateau 7x7 en 21x21
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < L; j++) {
            for (int m = 0; m < L*2 - 1; m++) {
                if (maze[i][j] == m) {
                    for (int k = i*3; k < i*3 + 3; k++) {
                        for (int l = j*3; l < j*3 + 3; l++) {
                            maze_affichage[k][l] = m;
                        }
                    }
                }

            }
        }
    }
    for (int i = 0; i < H*3; i++) {
        for (int j = 0; j < L*3; j++) {
            printf("%d ", maze_affichage[i][j]);
        }
        printf("\n");
    }
}


void afficher3(int maze[H][L], int maze_affichage[H*3][L*3]) { // afficher les tuiles (murs et tout)
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < L; j++) {
            if (maze[i][j] == 0) {
                maze_affichage[i*3][j*3] = 0xDB;
                maze_affichage[i*3][j*3 + 1] = 0x2B;
                maze_affichage[i*3][j*3 + 2] = 0xDB;
                maze_affichage[i*3 + 1][j*3] = 0xDB;
                maze_affichage[i*3 + 1][j*3 + 1] = 0x2B;
                maze_affichage[i*3 + 1][j*3 + 2] = 0xDB;
                maze_affichage[i*3 + 2][j*3] = 0xDB;
                maze_affichage[i*3 + 2][j*3 + 1] = 0x2B;
                maze_affichage[i*3 + 2][j*3 + 2] = 0xDB;
            }
            else if (maze[i][j] == 1) {
                maze_affichage[i*3][j*3] = 0xDB;
                maze_affichage[i*3][j*3 + 1] = 0xDB;
                maze_affichage[i*3][j*3 + 2] = 0xDB;
                maze_affichage[i*3 + 1][j*3] = 0x2B;
                maze_affichage[i*3 + 1][j*3 + 1] = 0x2B;
                maze_affichage[i*3 + 1][j*3 + 2] = 0x2B;
                maze_affichage[i*3 + 2][j*3] = 0xDB;
                maze_affichage[i*3 + 2][j*3 + 1] = 0x2B;
                maze_affichage[i*3 + 2][j*3 + 2] = 0xDB;
            }
            else if (maze[i][j] == 2) {
                maze_affichage[i*3][j*3] = 0xDB;
                maze_affichage[i*3][j*3 + 1] = 0x2B;
                maze_affichage[i*3][j*3 + 2] = 0xDB;
                maze_affichage[i*3 + 1][j*3] = 0xDB;
                maze_affichage[i*3 + 1][j*3 + 1] = 0x2B;
                maze_affichage[i*3 + 1][j*3 + 2] = 0x2B;
                maze_affichage[i*3 + 2][j*3] = 0xDB;
                maze_affichage[i*3 + 2][j*3 + 1] = 0xDB;
                maze_affichage[i*3 + 2][j*3 + 2] = 0xDB;
            }
        }
    }

    for (int i = 0; i < H*3; i++) {
        for (int j = 0; j < L*3; j++) {
            printf("%c", maze_affichage[i][j]);
        }
        printf("\n");
    }
}


int main() {

    Color(11, 0);
    int maze[H][L] = {{0, 1, 1, 2, 0, 2, 0}, {2, 1, 1, 2, 0, 0, 1}, {0, 2, 0, 2, 1, 2, 0}, {0, 1, 0, 2, 1, 2, 2}, {0, 1, 2, 0, 1, 0, 1}, {2, 0, 1, 2, 0, 1}, {2, 1, 1, 0, 2, 2}, {0, 1, 1, 2, 0, 2, 0}};
    int maze_affichage[H*3][L*3] = {0};
    afficher1(maze);
    afficher3(maze, maze_affichage);

    return 0;
}