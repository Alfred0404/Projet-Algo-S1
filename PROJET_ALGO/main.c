#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define TRUE 1
#define FALSE 0
#define HEIGHT 7
#define WIDTH 7


void Color(int CouleurTexte, int couleurFond) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurFond * 16 + CouleurTexte);
}



typedef struct {
    int id, x, y;
    char* paquet_cartes;
} Joueur;


typedef struct {
    int tresor, orientation;
    char type;
    Joueur player;
}Tuile;


int choisir_nb_joueurs() { // choisir le nombre de joueurs
    int nb_joueur;
    do {
        printf("Choisissez le nombre de joueur : \n");
        scanf("%d", &nb_joueur);
    } while (nb_joueur < 2 || nb_joueur > 4);
    printf("Vous avez choisi %d joueurs \n", nb_joueur);
    return nb_joueur;
}


Joueur* creer_joueurs(int nb_joueurs) {

    srand(time(NULL));
    Joueur* joueurs = (Joueur*) malloc(nb_joueurs * sizeof(Joueur));
    char cartes[24] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'};
    char cartes_melanges[24];
    int taille_cartes = 24;
    int taille_paquet = 24 / nb_joueurs;
    
    for (int i = 0; i < taille_cartes; i++) { // Melanger les cartes
        int index_aleatoire = rand() % (taille_cartes - i);
        cartes_melanges[i] = cartes[index_aleatoire];
        for (int j = index_aleatoire; j < taille_cartes - 1; j++) {
            cartes[j] = cartes[j + 1];
        }
    }


    for (int i = 0; i < nb_joueurs; i++) { // Creer les paquets de cartes
        joueurs[i].id = i + 1;
        joueurs[i].paquet_cartes = (char*) malloc((taille_paquet) * sizeof(char)); 

        for (int j = 0; j < taille_paquet; j++) {
            joueurs[i].paquet_cartes[j] = cartes_melanges[j + i * taille_paquet]; // Distribuer les cartes
        }
    }

    //placer les joueurs sur le plateau
    for (int i = 0; i < nb_joueurs; i++) {
        if (joueurs[i].id == 1) {
            joueurs[i].x = 0;
            joueurs[i].y = 0;
        }
        else if (joueurs[i].id == 2) {
            joueurs[i].x = 0;
            joueurs[i].y = WIDTH - 1;
        }
        else if (joueurs[i].id == 3) {
            joueurs[i].x = HEIGHT - 1;
            joueurs[i].y = 0;
        }
        else if (joueurs[i].id == 4) {
            joueurs[i].x = HEIGHT - 1;
            joueurs[i].y = WIDTH - 1;
        }
    }
    return joueurs;
}


void initialiser_plateau(Tuile plateau[HEIGHT][WIDTH], int nb_joueurs, Joueur* joueurs) { // initialiser plateau 7x7
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
            plateau[i][j].player.id = 0;
        }
    }
    // orienter les 16 tuiles fixes
    plateau[0][0].orientation = 1;
    plateau[0][WIDTH - 1].orientation = 2;
    plateau[HEIGHT - 1][0].orientation = 0;
    plateau[HEIGHT - 1][WIDTH - 1].orientation = 3;
    plateau[0][2].orientation = 0;
    plateau[0][4].orientation = 0;
    plateau[2][0].orientation = 3;
    plateau[4][0].orientation = 3;
    plateau[2][WIDTH - 1].orientation = 1;
    plateau[4][WIDTH - 1].orientation = 1;
    plateau[HEIGHT - 1][2].orientation = 2;
    plateau[HEIGHT - 1][4].orientation = 2;
    plateau[2][2].orientation = 3;
    plateau[2][4].orientation = 0;
    plateau[4][2].orientation = 2;
    plateau[4][4].orientation = 1;

    // placer les joueurs
    if (nb_joueurs == 2) {
        plateau[0][0].player = joueurs[0];
        plateau[0][WIDTH - 1].player = joueurs[1];
    }
    else if (nb_joueurs == 3) {
        plateau[0][0].player = joueurs[0];
        plateau[HEIGHT - 1][0].player = joueurs[1];
        plateau[0][WIDTH - 1].player = joueurs[2];
    }
    else if (nb_joueurs == 4) {
        plateau[0][0].player = joueurs[0];
        plateau[HEIGHT - 1][WIDTH - 1].player = joueurs[3];
        plateau[HEIGHT - 1][0].player = joueurs[2];
        plateau[0][WIDTH - 1].player = joueurs[1];
    }
}


void remplir_plateau(Tuile plateau[HEIGHT][WIDTH]) { // remplir plateau 7x7 aleatoirement
    srand(time(NULL));
    char tuiles_types[3] = { 'L', 'T', 'I' };
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i  % 2 != 0 || j % 2 != 0) {
                plateau[i][j].type = tuiles_types[rand() % 3];
                plateau[i][j].orientation = rand() % 3;
            }
        }
    }
}


void afficher_plateau_debug(Tuile plateau[HEIGHT][WIDTH]) { // afficher le type de chaque tuile
    printf("\nPlateau debug.\n");
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
            else if (plateau[i][j].type == 'I') {
                Color(10, 0);
                printf("%c ", plateau[i][j].type);
            }
        }
        Color(15, 0);
        printf("\n");
    }
}


void afficher_plateau(Tuile plateau[HEIGHT][WIDTH], int maze_affichage[HEIGHT*3][WIDTH*3], Joueur* joueurs) { // afficher les tuiles (murs, tresors, joueurs)
    printf("\nPlateau.\n");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (plateau[i][j].type == 'I') { // TUILE DE TYPE I
                maze_affichage[i*3][j*3] = 0xDB;
                maze_affichage[i*3][j*3 + 1] = 0xF0;
                maze_affichage[i*3][j*3 + 2] = 0xDB;
                maze_affichage[i*3 + 1][j*3] = 0xDB;
                maze_affichage[i*3 + 1][j*3 + 1] = 0xF0;
                maze_affichage[i*3 + 1][j*3 + 2] = 0xDB;
                maze_affichage[i*3 + 2][j*3] = 0xDB;
                maze_affichage[i*3 + 2][j*3 + 1] = 0xF0;
                maze_affichage[i*3 + 2][j*3 + 2] = 0xDB;
            }
            else if (plateau[i][j].type == 'T') { // TUILE DE TYPE T
                maze_affichage[i*3][j*3] = 0xDB;
                maze_affichage[i*3][j*3 + 1] = 0xDB;
                maze_affichage[i*3][j*3 + 2] = 0xDB;
                maze_affichage[i*3 + 1][j*3] = 0xF0;
                maze_affichage[i*3 + 1][j*3 + 1] = 0xF0;
                maze_affichage[i*3 + 1][j*3 + 2] = 0xF0;
                maze_affichage[i*3 + 2][j*3] = 0xDB;
                maze_affichage[i*3 + 2][j*3 + 1] = 0xF0;
                maze_affichage[i*3 + 2][j*3 + 2] = 0xDB;
            }
            else if (plateau[i][j].type == 'L') { // TUILE DE TYPE L
                maze_affichage[i*3][j*3] = 0xDB;
                maze_affichage[i*3][j*3 + 1] = 0xF0;
                maze_affichage[i*3][j*3 + 2] = 0xDB;
                maze_affichage[i*3 + 1][j*3] = 0xDB;
                maze_affichage[i*3 + 1][j*3 + 1] = 0xF0;
                maze_affichage[i*3 + 1][j*3 + 2] = 0xF0;
                maze_affichage[i*3 + 2][j*3] = 0xDB;
                maze_affichage[i*3 + 2][j*3 + 1] = 0xDB;
                maze_affichage[i*3 + 2][j*3 + 2] = 0xDB;
            }
            else if (plateau[i][j].type == '.') { // TUILE DE TYPE . (vide)
                maze_affichage[i*3][j*3] = 0xF0;
                maze_affichage[i*3][j*3 + 1] = 0xF0;
                maze_affichage[i*3][j*3 + 2] = 0xF0;
                maze_affichage[i*3 + 1][j*3] = 0xF0;
                maze_affichage[i*3 + 1][j*3 + 1] = 0xF0;
                maze_affichage[i*3 + 1][j*3 + 2] = 0xF0;
                maze_affichage[i*3 + 2][j*3] = 0xF0;
                maze_affichage[i*3 + 2][j*3 + 1] = 0xF0;
                maze_affichage[i*3 + 2][j*3 + 2] = 0xF0;
            }
        }
    }

    for (int i = 0; i < HEIGHT; i++) { // gerer les orientations des tuiles
        for (int j = 0; j < WIDTH; j++) {
            if (plateau[i][j].orientation == 1) {
                int tmp_coins = maze_affichage[i*3][j*3]; // a
                int tmp_arretes = maze_affichage[i*3][j*3 + 1]; // A
                maze_affichage[i*3][j*3] = maze_affichage[i*3 + 2][j*3]; // a = b
                maze_affichage[i*3 + 2][j*3] = maze_affichage[i*3 + 2][j*3 + 2]; // b = c
                maze_affichage[i*3 + 2][j*3 + 2] = maze_affichage[i*3][j*3 + 2]; // c = d
                maze_affichage[i*3][j*3 + 2] = tmp_coins; // d = a
                maze_affichage[i*3][j*3 + 1] = maze_affichage[i*3 + 1][j*3]; // A = B
                maze_affichage[i*3 + 1][j*3] = maze_affichage[i*3 + 2][j*3 + 1]; // B = C
                maze_affichage[i*3 + 2][j*3 + 1] = maze_affichage[i*3 + 1][j*3 + 2]; // C = D
                maze_affichage[i*3 + 1][j*3 + 2] = tmp_arretes; // D = A
            }
            else if (plateau[i][j].orientation == 2) {
                int tmp_coins1 = maze_affichage[i*3][j*3];
                int tmp_arretes1 = maze_affichage[i*3][j*3 + 1];
                int tmp_coins2 = maze_affichage[i*3 + 2][j*3];
                int tmp_arretes2 = maze_affichage[i*3 + 1][j*3];
                maze_affichage[i*3][j*3] = maze_affichage[i*3 + 2][j*3 + 2];
                maze_affichage[i*3][j*3 + 1] = maze_affichage[i*3 + 2][j*3 + 1];
                maze_affichage[i*3][j*3 + 2] = maze_affichage[i*3 + 2][j*3];
                maze_affichage[i*3 + 1][j*3] = maze_affichage[i*3 + 1][j*3 + 2];
                maze_affichage[i*3 + 1][j*3 + 2] = tmp_arretes2;
                maze_affichage[i*3 + 2][j*3] = tmp_coins2;
                maze_affichage[i*3 + 2][j*3 + 1] = tmp_arretes1;
                maze_affichage[i*3 + 2][j*3 + 2] = tmp_coins1;
            }
            else if (plateau[i][j].orientation == 3) {
                int tmp_coins = maze_affichage[i*3][j*3]; // a
                int tmp_arretes = maze_affichage[i*3][j*3 + 1]; //A
                maze_affichage[i*3][j*3] = maze_affichage[i*3 + 2][j*3]; // a = b
                maze_affichage[i*3 + 2][j*3] = maze_affichage[i*3 + 2][j*3 + 2]; // b = c
                maze_affichage[i*3 + 2][j*3 + 2] = maze_affichage[i*3 + 2][j*3]; // c = d
                maze_affichage[i*3 + 2][j*3] = tmp_coins; // d = a
                maze_affichage[i*3][j*3 + 1] = maze_affichage[i*3 + 1][j*3 + 2]; // A = B
                maze_affichage[i*3 + 1][j*3 + 2] = maze_affichage[i*3 + 2][j*3 + 1]; // B = C
                maze_affichage[i*3 + 2][j*3 + 1] = maze_affichage[i*3 + 1][j*3]; // C = D
                maze_affichage[i*3 + 1][j*3] = tmp_arretes; // D = A
            }
        }     
    }

    for (int i = 0; i < HEIGHT; i++) { // gerer les joueurs
        for (int j = 0; j < WIDTH; j++) {
            if (plateau[i][j].player.id == 0) {
                maze_affichage[i*3 + 1][j*3 + 1] = 0xF0;
            }
            else if (plateau[i][j].player.id == joueurs[0].id) {
                maze_affichage[i*3 + 1][j*3 + 1] = 0x03;
            }
            else if (plateau[i][j].player.id == joueurs[1].id) {
                maze_affichage[i*3 + 1][j*3 + 1] = 0x04;
            }
            else if (plateau[i][j].player.id == joueurs[2].id) {
                maze_affichage[i*3 + 1][j*3 + 1] = 0x05;
            }
            else if (plateau[i][j].player.id == joueurs[3].id) {
                maze_affichage[i*3 + 1][j*3 + 1] = 0x06;
            }
            else {
                maze_affichage[i*3 + 1][j*3 + 1] = 0xF0;
            }
        }
    }

    for (int i = 0; i < HEIGHT*3; i++) { // affichage du plateau
        for (int j = 0; j < WIDTH*3; j++) {
            printf("%c ", maze_affichage[i][j]);
        }
        printf("\n");
    }
}


void afficher_joueurs(Joueur* joueurs, int nb_joueurs) {
    Color(15, 0);
    printf("\nJoueurs.\n");
    int taille_paquet = 24 / nb_joueurs;
    for (int i = 0; i < nb_joueurs; i++) {
        if (joueurs[i].id == 1) {
            printf("Joueur %d (%c): (%d, %d)\n", joueurs[i].id, 0x03, joueurs[i].x, joueurs[i].y);
        }
        else if (joueurs[i].id == 2) {
            printf("Joueur %d (%c): (%d, %d)\n", joueurs[i].id, 0x04, joueurs[i].x, joueurs[i].y);
        }
        else if (joueurs[i].id == 3) {
            printf("Joueur %d (%c): (%d, %d)\n", joueurs[i].id, 0x05, joueurs[i].x, joueurs[i].y);
        }
        else if (joueurs[i].id == 4) {
            printf("Joueur %d (%c): (%d, %d)\n", joueurs[i].id, 0x06, joueurs[i].x, joueurs[i].y);
        }
        printf("\tPaquet de cartes : ");
        for (int j = 0; j < taille_paquet; j++) {
            printf("%c ", joueurs[i].paquet_cartes[j]);
        }
    printf("\n");
    }
}


void afficher_joueurs_debug(Joueur* joueurs, int nb_joueurs, Tuile plateau[HEIGHT][WIDTH]) {
    printf("\nJoueurs debug.\n");
    int taille_paquet = 24 / nb_joueurs;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%d ", plateau[i][j].player.id);
        }
        printf("\n");
    }
}


int menu() { // menu principal

    int choix = 0;

    Color(9,0);
    printf("\n~~~~~~ ! MENU PRINCIPAL ! ~~~~~~\n\n");
    Color(10,0);
    printf("1. Nouvelle partie \n");
    Color(14,0);
    printf("2. Regles et Credits \n");
    Color(12,0);
    printf("3. Quitter \n\n");
    Color(15,0);
    printf("Votre choix : ");
    Color(15,0);
    scanf("%d", &choix);

    return choix;
}


void regles_credits() {
    Color(10,0);
    printf("~~~~~~ ! REGLES ET CREDITS ! ~~~~~~ \n");
    Color(12,0);
    printf("\n- BUT DU JEU : \n");
    Color(14,0);
    printf("\n\tVous penetrez dans un labyrinthe enchante a la recherche de fabuleux tresors et de mysterieuses\n\tcreatures. Chacun d'entre vous essaye de creer des\n\tchemins pour atteindre le tresor qu'il convoite en faisant\n\tcoulisser astucieusement les couloirs.\n\tLe joueur qui aura trouve tous ses tresors et rejoint sa\n\tcase depart le premier sera declare vainqueur !\n\n");
    Color(12,0);
    printf("- DEROULEMENT DE LA PARTIE : \n\n");
    Color(14,0);
    printf("\t * Le tour d'un joueur se decompose en deux etapes :\n");
    printf("\t\t- Modifier les couloirs.\n");
    printf("\t\t- Deplacer son pion.\n\n");
    printf("\t* Quand vient son tour, le joueur doit essayer d'atteindre\n\tla case sur laquelle figure le meme tresor que sur la\n\tcarte superieure de sa pile.\n");
    printf("\n\t* Il peut alors D'ABORD modifier les couloirs pour creer un chemin\n\tvers cette case, et ENSUITE deplacer son pion.\n");
    printf("\n\t* Il peut modifier les couloirs en faisant glisser un couloir vers le haut, vers le bas,\n\tvers la gauche ou vers la droite. sur une ligne / colonne PAIRE.\n\n\t* Contrainte : Une plaque ne peut jamais etre reintroduite\n\ta l'endroit meme d'ou elle vient d'etre expulsee par le\n\tjoueur precedent.\n");
    printf("\n\t* Il peut deplacer son pion dans les 4 directions tant qu'il ne rencontre pas de murs.\n\tIl est aussi permis de rester sur place\n");
    printf("\n\t* Si le joueur rencontre un tresor, il le ramasse et place la carte tresor trouvee face visible a cote de sa pile.\n");
    Color(12,0);
    printf("- FIN DE PARTIE :\n");
    Color(14,0);
    printf("\n\t* La partie se termine quand un joueur a trouve tous ses tresors et est revenu sur sa case depart.\n\n");
    Color(12,0);
    printf("- CREDITS :\n");
    Color(14,0);
    printf("\n\t* Projet realise par : \n\n\t\tAlfred de Vulpian, Matheo Innocent, Jerry Cheng\n\n");
    Color(15,0);
}


int main() { // fonction principale

    int choice = menu();

    if (choice == 1) { // nouvelle partie et boucle de jeu
        Color(10,0);
        printf("\n\t~~~~~~ ! NOUVELLE PARTIE ! ~~~~~~\n\n");
        Color(15,0);

        Tuile plateau[HEIGHT][WIDTH];
        int maze_affichage[HEIGHT*3][WIDTH*3] = { 0 };
        int nb_joueurs = choisir_nb_joueurs();

        Joueur* joueurs = creer_joueurs(nb_joueurs);
        initialiser_plateau(plateau, nb_joueurs, joueurs);
        remplir_plateau(plateau);
        afficher_joueurs(joueurs, nb_joueurs);
        afficher_joueurs_debug(joueurs, nb_joueurs, plateau);
        afficher_plateau_debug(plateau);
        afficher_plateau(plateau, maze_affichage, joueurs);
    }
    else if (choice == 2) { // regles et credits
        regles_credits();
        main();
    }
    else if (choice == 3) {
        Color(10,0);
        printf("\n\t~~~~~~ ! A BIENTOT ! ~~~~~~ \n\n");
        Color(15,0);
        exit(0);
    }
    else { // choix invalide
        Color(12,0);
        printf("\n\t~~~~~~ ! CHOIX INVALIDE ! ~~~~~~ \n\n");
        Color(15,0);
        return 0;
    }
    
    return 0;
}
