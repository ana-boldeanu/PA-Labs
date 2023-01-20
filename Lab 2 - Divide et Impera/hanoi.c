#include <stdio.h>
/*
    Turnurile din Hanoi
    A = turn sursa
    B = turn destinatie
    C = turn auxiliar
*/

int nr_tranzitie = 1;

// O tranzitie 
void move(char A, char B) {
    printf("%d: %c -> %c\n", nr_tranzitie, A, B);      // Muta 1 disc din A in B
    nr_tranzitie++;
}

// Algoritm
void hanoi(int n, char A, char B, char C) {
    if (n > 0) {
        hanoi(n - 1, A, C, B);
        move(A, B);
        hanoi(n - 1, C, B, A);
    }
}


int main() {
    int n = 3;
    char A = 'A', B = 'B', C = 'C';

    hanoi(n, A, B, C);
    
    return 0;
}