#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
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
    int orientation;
    char type, tresor;
    Joueur player;
}Tuile;


int choisir_nb_joueurs() { // choisir le nombre de joueurs
    int nb_joueur = 0;
    do {
        printf("Choisissez le nombre de joueur : ");
        scanf("%d", &nb_joueur);
        printf("\n");
    } while (nb_joueur < 2 || nb_joueur > 4);
    printf("Vous avez choisi %d joueurs \n", nb_joueur);
    return nb_joueur;
}


Joueur* creer_joueurs(int nb_joueurs, char cartes[24]) {

    srand(time(NULL));
    Joueur* joueurs = (Joueur*) malloc(nb_joueurs * sizeof(Joueur));
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


void initialiser_plateau(Tuile plateau[HEIGHT][WIDTH], int nb_joueurs, Joueur* joueurs, char cartes[24]) { // initialiser plateau 7x7
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 && j == 0 || i == 0 && j == HEIGHT - 1 || i == WIDTH - 1 && j == 0 || i == WIDTH - 1 && j == HEIGHT - 1) {
                plateau[i][j].type = 'L';
                plateau[i][j].tresor = '.';

            }
            else if (i % 2 == 0 && j % 2 == 0) {
                plateau[i][j].type = 'T';
                if (cartes[0] != '\0') {
                    plateau[i][j].tresor = cartes[0];
                    for (int k = 0; k < 23; k++) {
                        cartes[k] = cartes[k + 1];
                    }
                    cartes[23] = '\0';
                }
            }
            else {
                plateau[i][j].type = '.';
                plateau[i][j].tresor = '.';
            }
            plateau[i][j].player.id = 0;
        }
    }
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

   for (int i = 0; i < nb_joueurs; i++) {
       plateau[joueurs[i].x][joueurs[i].y].player = joueurs[i];
   }
}


void free_memoire(Joueur* joueurs, int nb_joueurs) { // liberer la memoire
    for (int i = 0; i < nb_joueurs; i++) {
        free(joueurs[i].paquet_cartes);
    }
    free(joueurs);
}


void remplir_plateau_2(Tuile plateau[HEIGHT][WIDTH], char cartes[24]) { // remplir le plateau avec 6 tuiles T avec tresor, 6 tuiles L avec tresor, 10 tuiles L sans tresor, et 12 tuiles I sans tresor
    srand(time(NULL));
    int liste[33];
    int compteur;
    for (int i = 0; i < 33; i++) {
        liste[i] = i;
    }
    for (int i = 0; i < 33; i++) {
        int j = rand() % 33;
        int temp = liste[i];
        liste[i] = liste[j];
        liste[j] = temp;
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i % 2 != 0 || j % 2 != 0) {
                compteur = liste[0];
                int placer_tresor = rand() % 3;
                if (compteur < 6 && compteur >= 0 && cartes[0] != '\0') { // 6 tuiles T avec tresor
                    plateau[i][j].type = 'T';
                    plateau[i][j].orientation = rand() % 3;
                    if (cartes[0] != '\0' && placer_tresor == 1 || placer_tresor == 2 && cartes[0] != '\0' || placer_tresor == 0 && cartes[0] != '\0') {
                        plateau[i][j].tresor = cartes[0];
                        for (int k = 0; k < 23; k++) {
                            cartes[k] = cartes[k + 1];
                        }
                        cartes[23] = '\0';
                    }
                }
                else if (compteur < 12 && compteur >= 6 && cartes[0] != '\0') { // 6 tuiles L avec tresor
                    plateau[i][j].type = 'L';
                    plateau[i][j].orientation = rand() % 3;
                    if (cartes[0] != '\0' && placer_tresor == 1 || placer_tresor == 2 && cartes[0] != '\0' || placer_tresor == 0 && cartes[0] != '\0') {
                        plateau[i][j].tresor = cartes[0];
                        for (int k = 0; k < 23; k++) {
                            cartes[k] = cartes[k + 1];
                        }
                        cartes[23] = '\0';
                    }
                }
                else if (compteur < 22 && compteur >= 12) { // 10 tuiles L sans tresor
                    plateau[i][j].type = 'L';
                    plateau[i][j].orientation = rand() % 3;
                    plateau[i][j].tresor = '.';
                }
                else if (compteur >= 22 && compteur < 34){ // 12 tuiles I sans tresor ok
                    plateau[i][j].type = 'I';
                    plateau[i][j].orientation = rand() % 3;
                    plateau[i][j].tresor = '.';
                }
                for (int k = 0; k < 32; k++) {
                    liste[k] = liste[k + 1];
                }
            }
        }
    }
}


Tuile tuile_restante_test(Tuile plateau[HEIGHT][WIDTH], char cartes[24]) {
    Tuile tuile_restante;
    tuile_restante.type = '.';
    tuile_restante.orientation = 0;
    int nb_lt = 6, nb_tt = 6, nb_l = 10, nb_i = 12;
    int indice = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (plateau[i][j].type == 'L' && plateau[i][j].tresor == '.') {
                nb_l--;
            }
            else if (plateau[i][j].type == 'L' && plateau[i][j].tresor != '.') {
                nb_lt--;
            }
            else if (plateau[i][j].type == 'T' && plateau[i][j].tresor != '.') {
                nb_tt--;
            }
            else if (plateau[i][j].type == 'I') {
                nb_i--;
            }
        }
    }
    // assigne le type de tuile  dont le compteur vaut 1
    if (nb_lt == 1) {
        tuile_restante.type = 'L';
        tuile_restante.tresor = cartes[0];
    }
    else if (nb_tt == 1) {
        tuile_restante.type = 'T';
        tuile_restante.tresor = cartes[0];
    }
    else if (nb_l == 1) {
        tuile_restante.type = 'L';
        tuile_restante.tresor = '.';
    }
    else if (nb_i == 1) {
        tuile_restante.type = 'I';
        tuile_restante.tresor = '.';
    }

    tuile_restante.player.id = 0;
    return tuile_restante;
}


void afficher_plateau(Tuile plateau[HEIGHT][WIDTH], int maze_affichage[HEIGHT*3][WIDTH*3], Joueur* joueurs) { // afficher les tuiles (murs, tresors, joueurs)
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
    for (int i = 0; i < HEIGHT; i++) { //gerer les tresors
        for (int j = 0; j < WIDTH; j++) {
            if (plateau[i][j].tresor != '.') {
                maze_affichage[i*3 + 1][j*3 + 1] = plateau[i][j].tresor;
            }
            else if (plateau[i][j].tresor == '.' && plateau[i][j].player.id == 0) {
                maze_affichage[i*3 + 1][j*3 + 1] = 0xF0;
            }
        }
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (plateau[i][j].tresor != '.' && plateau[i][j].player.id != 0) {
                if (plateau[i][j].player.id == joueurs[0].id) {
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
            }
        }
    }

    for (int i = 0; i < HEIGHT*3; i++) { // affichage du plateau
        for (int j = 0; j < WIDTH*3; j++) {
            if (maze_affichage[i][j] == 0x03) {
                Color(9, 15);
            }
            else if (maze_affichage[i][j] == 0x04) {
                Color(12, 15);
            }
            else if (maze_affichage[i][j] == 0x05) {
                Color(2, 15);
            }
            else if (maze_affichage[i][j] == 0x06) {
                Color(14, 15);
            }
            else if (maze_affichage[i][j] == 0xDB) {
                Color(8, 8);
            }
            else {
                Color(0, 15);
            }
            printf("%c ", maze_affichage[i][j]);
        }
        Color(15, 0);
        printf("\n");
    }
    Color(15, 0);
}


void afficher_joueurs(Joueur* joueurs, int nb_joueurs) { // affichage des infos des joueurs
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
    if (choix == 3) {
        exit(0);
    }
    else if (choix == 2) {
        regles_credits();
        menu();
    }
    return choix;
}


void regles_credits() { // regles et credits
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
    printf("\n\t* Pour vous deplacer sur le plateau, utilisez les touches les fleches directionnelles, ou echap pour passer votre tour.\n\n");
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


int victoire (Joueur* joueurs, int nb_joueurs) {
    // parcourt les joueurs et verifie si un joueur a gagne
    int vainqueur = 0;
    for (int i = 0; i < nb_joueurs; i++) {
        if (joueurs[i].paquet_cartes[0] == '\0') {
            vainqueur = joueurs[i].id;
            Color(10,0);
            printf("\nLe joueur %d a gagne !\n", vainqueur);
            return 0;
        }
        else {
            return 1;
        }
    }
    Color(15,0);
}


void ramasser_tresor(Joueur* joueurs,int taille_pile, int joueur_actuel, Tuile plateau[HEIGHT][WIDTH]) {
    Joueur joueur_qui_ramasse = joueurs[joueur_actuel];
    int taille_pile_joueur = taille_pile;
    if (plateau[joueur_qui_ramasse.x][joueur_qui_ramasse.y].tresor != '.' && joueur_qui_ramasse.paquet_cartes[0] == plateau[joueur_qui_ramasse.x][joueur_qui_ramasse.y].tresor) {
        for (int i = 0; i < taille_pile_joueur; i++) {
            joueur_qui_ramasse.paquet_cartes[i] = joueur_qui_ramasse.paquet_cartes[i+1];
        }
        plateau[joueur_qui_ramasse.x][joueur_qui_ramasse.y].tresor = '.'; // on enleve le tresor de la case
        Color(10,0);
        printf("Vous avez ramasse un tresor !\n");
        Color(15,0);
        //for (int i = 0; i < taille_pile_joueur; i++) {
        //    printf("%c ", joueur_qui_ramasse.paquet_cartes[i]);
       // }
        printf("\n");
    }
}


void deplacer_joueur(Joueur* joueurs, int joueur_actuel, int x, int y, Tuile plateau[HEIGHT][WIDTH]) {
    Joueur joueur_a_deplacer = joueurs[joueur_actuel];

    int id_joueur = joueur_a_deplacer.id;

    int ancien_x = joueur_a_deplacer.x;
    int ancien_y = joueur_a_deplacer.y;

    plateau[ancien_x][ancien_y].player.id = 0;
    plateau[ancien_x][ancien_y].player.x = 0;
    plateau[ancien_x][ancien_y].player.y = 0;

    if (plateau[x][y].player.id == 0) {
        joueur_a_deplacer.x = x;
        joueur_a_deplacer.y = y;
        plateau[x][y].player.id = id_joueur;
        plateau[x][y].player.x = x;
        plateau[x][y].player.y = y;
        joueurs[joueur_actuel] = joueur_a_deplacer;
    }
}


void deplacer_joueur_fleches(Joueur* joueurs, int joueur_actuel, Tuile plateau[HEIGHT][WIDTH], int maze_affichage[HEIGHT*3][WIDTH*3], int taille_pile) {
    int touche = 0;
    int x = joueurs[joueur_actuel].x;
    int y = joueurs[joueur_actuel].y;
    int deplacable = 1;
    while (touche != 13 && deplacable == 1) { // 27 = echap
        touche = getch();
        printf("\nTresor a ramasser : %c\n\n", joueurs[joueur_actuel].paquet_cartes[0]);
        switch (touche) {
            case 72: // haut
                if (x > 0 && maze_affichage[x*3][y*3 + 1] == 0xF0 && maze_affichage[(x-1)*3+2][y*3 + 1] == 0xF0 && plateau[x - 1][y].player.id == 0) {
                    deplacer_joueur(joueurs, joueur_actuel, x - 1, y, plateau);
                    x--;
                }
                break;
            case 80: // bas
                if (x < HEIGHT - 1 && maze_affichage[x*3 + 2][y*3 + 1] == 0xF0 && maze_affichage[(x+1)*3][y*3 + 1] == 0xF0 && plateau[x + 1][y].player.id == 0) {
                    deplacer_joueur(joueurs, joueur_actuel, x + 1, y, plateau);
                    x++;
                }
                break;
            case 75: // gauche
                if (y > 0 && maze_affichage[x*3 + 1][y*3] == 0xF0 && maze_affichage[x*3 + 1][(y-1)*3+2] == 0xF0  && plateau[x][y - 1].player.id == 0) {
                    deplacer_joueur(joueurs, joueur_actuel, x, y - 1, plateau);
                    y--;
                }
                break;
            case 77: // droite
                if (y < WIDTH - 1 && maze_affichage[x*3 + 1][y*3 + 2] == 0xF0 && maze_affichage[x*3 + 1][(y+1)*3] == 0xF0 && plateau[x][y + 1].player.id == 0) {
                    deplacer_joueur(joueurs, joueur_actuel, x, y + 1, plateau);
                    y++;
                }
                break;
            case 27: // entrer
                menu();
        }
        joueurs[joueur_actuel].x = x;
        joueurs[joueur_actuel].y = y;

        ramasser_tresor(joueurs, taille_pile, joueur_actuel, plateau);
        afficher_plateau(plateau, maze_affichage, joueurs);
    }
    Color(4, 0);
    printf("\nFin du tour !\n");
    Color(15, 0);
}


Tuile deplacer_tuile(Joueur* joueurs, Tuile plateau[HEIGHT][WIDTH], Tuile tuile_en_plus, int tuile_i, int tuile_j, int joueur_actuel, int nb_joueurs) {
    Tuile tuile_temp;
    tuile_temp.tresor = '.';
    if (tuile_j == 0 && tuile_i % 2 != 0) { 
        tuile_temp = plateau[tuile_i][WIDTH - 1];
        for (int j = WIDTH - 1; j > 0; j--) {
            plateau[tuile_i][j] = plateau[tuile_i][j - 1];
        }
        for (int k = 0; k < nb_joueurs; k++) {
            if (joueurs[k].x == tuile_i && joueurs[k].y == 0) {
                joueurs[k].y++;
            }
        }
        plateau[tuile_i][0] = tuile_en_plus;
    }
    else if (tuile_j == WIDTH - 1 && tuile_i % 2 != 0) {
        tuile_temp = plateau[tuile_i][0];
        for (int j = 0; j < WIDTH - 1; j++) {
            plateau[tuile_i][j] = plateau[tuile_i][j + 1];
        }
        for (int k = 0; k < nb_joueurs; k++) {
            if (joueurs[k].x == tuile_i && joueurs[k].y == WIDTH - 1) {
                joueurs[k].y--;
            }
        }
        plateau[tuile_i][WIDTH - 1] = tuile_en_plus;
    }
    else if (tuile_i == 0 && tuile_j % 2 != 0) {
        tuile_temp = plateau[ HEIGHT - 1][tuile_j];
        for (int i = HEIGHT - 1; i > 0; i--) {
            plateau[i][tuile_j] = plateau[i - 1][tuile_j];
        }
        for (int k = 0; k < nb_joueurs; k++) {
            if (joueurs[k].x == 0 && joueurs[k].y == tuile_j) {
                joueurs[k].x++;
            }
        }
        plateau[0][tuile_j] = tuile_en_plus;
    }
    else if (tuile_i == HEIGHT - 1 && tuile_j % 2 != 0) {
        tuile_temp = plateau[0][tuile_j];
        for (int i = 0; i < HEIGHT - 1; i++) {
            plateau[i][tuile_j] = plateau[i + 1][tuile_j];
        }
        for (int k = 0; k < nb_joueurs; k++) {
            if (joueurs[k].x == HEIGHT - 1 && joueurs[k].y == tuile_j) {
                joueurs[k].x--;
            }
        }
        plateau[HEIGHT - 1][tuile_j] = tuile_en_plus;
    }
    if (tuile_temp.player.id != 0) {
        deplacer_joueur(joueurs, tuile_temp.player.id - 1, tuile_i, tuile_j, plateau);
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            for (int k = 0; k < nb_joueurs; k++) {
                if (plateau[i][j].player.id == joueurs[k].id) {
                    joueurs[k].x = i;
                    joueurs[k].y = j;
                }
            }
        }
    }
    tuile_temp.player.id = 0;
    //afficher_joueurs_debug(joueurs, nb_joueurs, plateau);
    return tuile_temp;
}


int main() {

    int choice = menu();
    char cartes[24] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'};
    char carte_2[24] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'};

    Tuile plateau[HEIGHT][WIDTH];

    int maze_affichage[HEIGHT*3][WIDTH*3] = { 0 }, nb_joueurs = choisir_nb_joueurs(), num_joueur = 0, taille_pile = 24 / nb_joueurs;
    Joueur* joueurs = creer_joueurs(nb_joueurs, cartes);
    
    initialiser_plateau(plateau, nb_joueurs, joueurs, carte_2);
    remplir_plateau_2(plateau, carte_2);

    Tuile tuile_en_plus = tuile_restante_test(plateau, cartes);
    
    if (choice == 1) { // nouvelle partie et boucle de jeu
    
        Color(10,0);
        printf("\n~~~~~~~~~~ ! NOUVELLE PARTIE ! ~~~~~~~~~~\n\n");
        Color(15,0);
        
        afficher_joueurs(joueurs, nb_joueurs);
        while (victoire(joueurs, nb_joueurs) == 1) {
            
            int tuile_i, tuile_j;

            Color(10,0);
            printf("\n~~~~~~~~~~ ! TOUR DU JOUEUR %d ! ~~~~~~~~~\n\n", num_joueur + 1);
            Color(15,0);
            printf("Tresor a trouver : %c\n", joueurs[num_joueur].paquet_cartes[0]);
            Color(10,0);
            printf("\n~~~~~~~~~~ Deplacement de tuile ~~~~~~~~~~\n\n");
            Color(15,0);

            afficher_plateau(plateau, maze_affichage, joueurs);
            printf("\nTuile a inserer : %c\nOrientation : %d\nTresor : %c\n\n", tuile_en_plus.type, tuile_en_plus.orientation, tuile_en_plus.tresor);
            
            do {
                printf("Entrez une orientation (0 = normal, 1 = 90 deg, 2 = 180 deg, 3 = 270) : ");
                scanf("%d", &tuile_en_plus.orientation);
                printf("\n");
            } while (tuile_en_plus.orientation < 0 || tuile_en_plus.orientation > 3);

            do {
                printf("Entrez les coordonnees (i, j) : ");
                scanf("%d %d", &tuile_i, &tuile_j);
                printf("\n");
            } while (tuile_i % 2 == 0 && tuile_j % 2 == 0 || tuile_i % 2 != 0 && tuile_j % 2 != 0 || tuile_i < 0 || tuile_i >= HEIGHT || tuile_j < 0 || tuile_j >= WIDTH);

            tuile_en_plus = deplacer_tuile(joueurs, plateau, tuile_en_plus, tuile_i, tuile_j, num_joueur, nb_joueurs);
            afficher_plateau(plateau, maze_affichage, joueurs);

            Color(10,0);
            printf("\n~~~~~~~~~~ Deplacement de joueur ~~~~~~~~~~\n");
            Color(15,0);
            deplacer_joueur_fleches(joueurs, num_joueur, plateau, maze_affichage, taille_pile);
            afficher_plateau(plateau, maze_affichage, joueurs);
            num_joueur = (num_joueur + 1) % nb_joueurs; // on passe au joueur suivant
        }
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
    free_memoire(joueurs, nb_joueurs);
    return 0;
}
