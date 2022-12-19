#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct {
    int joueur, tresor, orientation;
    char type;
}Tuile;

void debut_partie() {
    printf("~~~~~~ ! NOUVELLE PARTIE ! ~~~~~~");
}

int main() {
    debut_partie();
    
    return 0;
}