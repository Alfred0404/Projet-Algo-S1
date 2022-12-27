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


typedef struct  {
    int id, x, y;
    char* paquet_cartes;
} Joueur;


Joueur* initialiser_joueurs(Joueur liste_joueurs[], int nb_joueurs) {
    
    for (int i = 1; i < nb_joueurs + 1; i++) {
        liste_joueurs[i].id = i + 1;
        liste_joueurs[i].paquet_cartes = (char*)malloc(24 / nb_joueurs * sizeof(char));
        if (liste_joueurs[i].id == 1) {
            liste_joueurs[i].x = 0;
            liste_joueurs[i].y = 0;
        }
        else if (liste_joueurs[i].id == 2) {
            liste_joueurs[i].x = 0;
            liste_joueurs[i].y = L - 1;
        }
        else if (liste_joueurs[i].id == 3) {
            liste_joueurs[i].x = H - 1;
            liste_joueurs[i].y = 0;
        }
        else if (liste_joueurs[i].id == 4) {
            liste_joueurs[i].x = H - 1;
            liste_joueurs[i].y = L - 1;
        }
    }
    return liste_joueurs;
}


Joueur* distribuer_cartes(Joueur liste_joueurs[], int nb_joueurs, char cartes[24]) {
    srand(time(NULL));
    int index;
    int taille_paquet = 24 / nb_joueurs;
    for (int i = 0; i < nb_joueurs; i++) {
        for (int j = 0; j < 24; j++) {
            index = rand() % 24;
            liste_joueurs[i].paquet_carte[j] = cartes[index];
            for (int k = index; k < 24 - 1; k++) {
                cartes[k] = cartes[k + 1];
            }
        }
    }
    return liste_joueurs;
}


// afficher les cartes d'un joueur
void afficher_cartes(char paquet_carte[], int nb_joueurs) {
    for (int i = 0; i < 24 / nb_joueurs; i++) {
        printf("%c ", paquet_carte[i]);
    }
    printf("\n");
}


void afficher_joueurs(Joueur liste_joueurs[], int nb_joueurs) {
    for (int i = 0; i < nb_joueurs; i++) {
        printf("Joueur %d : (%d, %d)\n", liste_joueurs[i].id, liste_joueurs[i].x, liste_joueurs[i].y);
    }
}


int main() {

    srand(time(NULL));
    int nb_joueurs;
    printf("Nombre de joueurs : ");
    scanf("%d", &nb_joueurs);

    char cartes[24] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'};

    Joueur* liste_joueurs = (Joueur*)malloc(nb_joueurs * sizeof(Joueur));
    initialiser_joueurs(liste_joueurs, nb_joueurs);
    afficher_joueurs(liste_joueurs, nb_joueurs);
    distribuer_cartes(liste_joueurs, nb_joueurs, cartes);
    printf("%d\n", liste_joueurs[1].id);

    return 0;
}