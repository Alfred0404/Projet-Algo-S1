#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define H 7
#define L 7

int main() {

    char a[50] = "Hello ";
    int nombre = 1;
    char nombre_2[50];

    itoa(nombre, nombre_2, 10);
    char* cat = strcat(a, nombre_2);
    printf("%s", cat);

    return 0;
}