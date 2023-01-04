#include <stdio.h>
#include <conio.h>

#define WIDTH 7
#define HEIGHT 7

typedef struct {
    int id, x, y;
    char* paquet_cartes;
} Joueur;


// Création du tableau
char board[HEIGHT][WIDTH] = {
    {'*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', 'X', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*'}
};

// Fonction pour afficher le tableau
void print_board() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c ", board[y][x]);
        }
        printf("\n");
    }
}

void deplacement() {
    // Initialisation de la position du joueur
    int player_x = 3;
    int player_y = 3;

    // Boucle principale
    int run = 1;
    while (run) {
        // Affichage du tableau
        print_board();
        board[player_y][player_x] = '*';

        // Lecture de l'input du joueur
        int ch = getch();
        switch (ch) {
            case 72: // Flèche haut
                player_y--;
                break;
            case 80: // Flèche bas
                player_y++;
                break;
            case 75: // Flèche gauche
                player_x--;
                break;
            case 77: // Flèche droite
                player_x++;
                break;
            case 27: // Touche echap
                run = 0;
                break;
            default:
                printf("Mouvement non valide\n");
                continue;
        }

        if (player_x < 0) {
            player_x = 0;
        }
        if (player_x >= WIDTH) {
            player_x = WIDTH - 1;
        }
        if (player_y < 0) {
            player_y = 0;
        }
        if (player_y >= HEIGHT) {
            player_y = HEIGHT - 1;
        }

        // Mise à jour de la position du joueur dans le tableau
        board[player_y][player_x] = 'X';
        printf("\n");
    }
}

//cree une fonction deplacement pour le joueur



int main() {
    deplacement();
    return 0;
}