#include <stdio.h>
#include <stdlib.h>


int main(){
    int a = 5, b = 6, c = 7, d = 8;

    printf("Avant permutation :\n%d %d %d %d\n", a, b, c, d);

    //permute a, b, c, d
    int temp = a;
    a = b;
    b = c;
    c = d;
    d = temp;

    printf("Après permutation :\n%d %d %d %d\n", a, c, b, d);

    return 0;
}