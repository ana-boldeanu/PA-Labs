#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * k-garduri pentru n = 6 (lungimea gardului), k = 2 (inaltimea scandurii/gardului)
 * Scandura are dimensiunile 1 x k. Se pot aranja scanduri vertical sau orizontal.
 * In cate moduri poate fi construit gardul de lungime n?
 * 
 * Recurenta:
 *      D[i] = D[i - 1] + D[i - k]  // adaug k orizontale, la gardul de lungime i - k
 *                                                      sau
 *                                  // adaug 1 verticala, la gardul de lungime i - 1
 * 
 * Rezultatul final este D[n]
 */

const int n = 6, k = 2;

int *k_garduri(int n, int k) {
    int *D = calloc(n + 1, sizeof(int));                // numarul solutiilor
    char ***garduri = calloc(n + 1, sizeof(char**));    // solutiile efective

    for (int i = 0; i <= n; i++) {
        garduri[i] = calloc(100, sizeof(char*));
        for (int j = 0; j < 100; j++) {
            garduri[i][j] = calloc(100, sizeof(char));
        }
    }

    // Cazuri de baza
    D[0] = 1;   // 1 solutie pt lungime 0   { }
    D[1] = 1;   // 1 solutie pt lungime 1   { 1v } 
    strcat(garduri[1][0], "1v ");

    for (int i = 2; i <= n; i++) {
        // Relatia de recurenta
        D[i] = D[i - 1] + D[i - k];

        // Construirea solutiilor
        for (int j = 0; j < D[i - 1]; j++) {
            strcat(garduri[i][j], garduri[i - 1][j]);
            strcat(garduri[i][j], "1v ");
        }
        for (int p = 0; p < D[i - k]; p++) {
            strcat(garduri[i][D[i - 1] + p], garduri[i - k][p]);
            strcat(garduri[i][D[i - 1] + p], "2o ");
        }

        // Afisarea solutiilor
        if (i == 6) {
            printf("i = %d:\n", i);
            for (int nr = 0; nr < D[i]; nr++) {
                printf("\t%2d:  %s\n", nr, garduri[i][nr]);
            }            
        }
    }

    return D;
}


int main() {
    int *D = k_garduri(n, k);
    printf("Numarul solutiilor este D[%d] = %d\n", n, D[n]);

    return 0;
}