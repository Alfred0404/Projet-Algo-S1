#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define H 7
#define L 7


typedef struct {
    int id, x, y;
    char* paquet_cartes;
} Joueur;


typedef struct {
    int tresor, orientation;
    Joueur joueur;
} Tuile;


int demander_nb_joueurs() {
    int nb_joueurs;
    printf("Entrez le nombre de joueurs : ");
    scanf("%d", &nb_joueurs);
    return nb_joueurs;
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
            joueurs[i].y = L - 1;
        }
        else if (joueurs[i].id == 3) {
            joueurs[i].x = H - 1;
            joueurs[i].y = 0;
        }
        else if (joueurs[i].id == 4) {
            joueurs[i].x = H - 1;
            joueurs[i].y = L - 1;
        }
    }

    return joueurs;
}


void afficher_joueurs(Joueur* joueurs, int nb_joueurs) {
    int taille_paquet = 24 / nb_joueurs;
    for (int i = 0; i < nb_joueurs; i++) {
        printf("Joueur %d : (%d, %d)\n", joueurs[i].id, joueurs[i].x, joueurs[i].y);
        printf("\tPaquet de cartes : ");
        for (int j = 0; j < taille_paquet; j++) {
            printf("%c ", joueurs[i].paquet_cartes[j]);
        }
    printf("\n");
    }
}


int main() {

    int nb_joueurs = demander_nb_joueurs();
    Joueur* joueurs = creer_joueurs(nb_joueurs);
    afficher_joueurs(joueurs, nb_joueurs);

    for (int i = 0; i < nb_joueurs; i++) {
        free(joueurs[i].paquet_cartes);
    }
    free(joueurs);

    return 0;
}