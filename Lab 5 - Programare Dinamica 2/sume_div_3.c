#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Lab 2 - Divide et Impera/print_array.h"

/**
 * Se da un sir de n numere naturale. Cate sume putem forma, care au restul 0
 * la impartirea cu 3?
 * 
 * Recurenta
 *      D[i][j] = nr. sumelor, folosind elementele 1..i, care au restul j
 *      i = {1 .. n}, j = {0, 1, 2}
 * 
 * Rezultatul final este D[n][0]
 */


int **sume(int *v, int n) {
    // Matricea solutiilor (nr. de sume)
    int **D = calloc(n + 1, sizeof(int*));
    for (int i = 0; i <= n; i++) {
        D[i] = calloc(3, sizeof(int));
    }

    // Cazuri de baza
    D[0][0] = 0;
    D[0][1] = 0;
    D[0][2] = 0;

    // Relatiile de recurenta
    for (int i = 1; i <= n; i++) {
        if (v[i] % 3 == 0) {
            D[i][0] = 2 * D[i - 1][0] + 1;
            D[i][1] = 2 * D[i - 1][1];
            D[i][2] = 2 * D[i - 1][2];

        } else if (v[i] % 3 == 1) {
            D[i][0] = D[i - 1][0] + D[i - 1][2];
            D[i][1] = D[i - 1][1] + D[i - 1][0] + 1;
            D[i][2] = D[i - 1][2] + D[i - 1][1];

        } else {
            D[i][0] = D[i - 1][0] + D[i - 1][1];
            D[i][1] = D[i - 1][1] + D[i - 1][2];
            D[i][2] = D[i - 1][2] + D[i - 1][0] + 1;
        }
    }

    return D;
}

void afisare_sume(int *v, int n, int **D) {
    int **sume = calloc(20, sizeof(int*));
    for(int i = 0; i < 20; i++) {
        sume[i] = calloc(n + 1, sizeof(int));
    }
    int nr0 = 0, nr1 = 0, nr2 = 0;
    int i0, i1, i2;

    for (int i = 1; i <= n; i++) {
        if (v[i] % 3 == 0) {
            i0 = nr0; i1 = nr1; i2 = nr2;
            sume[nr0++][0] = v[i];

            for (int j = 0; j < i0; j++) {
                sume[nr0++][0] = sume[j][0] + v[i];
            }
            for (int j = 0; j < i1; j++) {
                sume[nr1++][1] = sume[j][1] + v[i];
            }
            for (int j = 0; j < i2; j++) {
                sume[nr2++][2] = sume[j][2] + v[i];
            }

        } else if (v[i] % 3 == 1) {
            i0 = nr0; i1 = nr1; i2 = nr2;
            sume[nr1++][1] = v[i];

            for (int j = 0; j < i2; j++) {
                sume[nr0++][0] = sume[j][2] + v[i];
            }
            for(int j = 0; j < i0; j++) {
                sume[nr1++][1] = v[i] + sume[j][0];
            }
            for(int j = 0 ; j < i1 ; j++) {
                sume[nr2++][2] = v[i] + sume[j][1];
            }

        } else {
            i0 = nr0; i1 = nr1; i2 = nr2;
            sume[nr2++][2] = v[i];

            for(int j = 0 ; j < i1; j++) {
                sume[nr0++][0] = sume[j][1] + v[i]; 
            }
            for(int j = 0 ; j < i2 ; j++) {
                sume[nr1++][1] = sume[j][2] + v[i]; 
            }
            for(int j = 0 ; j < i0 ; j++) {
                sume[nr2++][2] = sume[j][0] + v[i]; 
            }
        }
    }

    for(int i = 0 ; i < nr0 ; i++) {
        printf("%d ", sume[i][0]);
    }
    printf("\n");
}

int main() {
    int v[5] = {0, 3, 1, 2, 4};
    int n = 4;

    int **D = sume(v, n);
    printf("Se pot forma D[%d][0] = %d sume\n", n, D[n][0]);

    afisare_sume(v, n, D);
}