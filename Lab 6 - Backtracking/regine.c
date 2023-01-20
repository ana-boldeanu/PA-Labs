#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void print_sol(int *v, int n) {
    for (int i = 1; i <= n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

bool validare(int *v, int k, int lungSol, int initVal) {
    // Toate elementele puse in stiva pana acum sa fie diferite 2 cate 2
    // (reginele se afla pe coloane diferite)
    for (int i = 1; i <= lungSol; i++) {
        for (int j = 1; j <= lungSol ; j++) {
            if (i != j) {
                if (v[i] == v[j] && v[i] != initVal) {
                    return false;
                }
            }
        }
    }

    // Reginele nu se ataca pe diagonale
    for (int j = 1; j <= k; j++) {
        for (int i = 1; i <= k; i++) {
            if (i > j) {
                if (i - j == abs(v[i] - v[j])) {
                    return false;
                }
            } 
        } 
    }

    return true;
}

// In stiva, i reprezinta linia si v[i] coloana pe care se afla o regina
void regine_backtrack(int *sol, int lungSol, int initVal, int val, int max) {
    int nr_sol = 0;

    for (int i = 0; i <= lungSol; i++) {
        sol[i] = initVal;
    }

    int i = 1;
    while (i >= 1) {
        bool valid = false;

        while (!valid && sol[i] <= max) {
            sol[i] += val;
            valid = validare(sol, i, lungSol, initVal);
        }

        if (sol[i] <= max) {
            if (i == lungSol) {
                printf("Solutie #%d - ", ++nr_sol);
                print_sol(sol, lungSol);

            } else {
                i++;
            }

        } else {
            sol[i] = initVal;
            i--;
        }
    }
}


int main() {
    int n = 4;  // Numarul reginelor din problema

    int lungSol = n, max = n, initVal = 0, val = 1;
    int *sol = calloc(lungSol + 1, sizeof(int));

    regine_backtrack(sol, lungSol, initVal, val, max);

    return 0;
}