#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void print_sol(int *v, int n) {
    for (int i = 1; i <= n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

bool validare(int *v, int lungSol, int initVal) {
    // Toate elementele puse in stiva pana acum sa fie diferite 2 cate 2
    // (un numar apare o singura data intr-o permutare)
    for (int i = 1; i <= lungSol; i++) {
        for (int j = 1; j <= lungSol ; j++) {
            if (i != j) {
                if (v[i] == v[j] && v[i] != initVal) {
                    return false;
                }
            }
        }
    }
    return true;
}

void permutari_backtrack(int *sol, int lungSol, int initVal, int val, int max) {
    int nr_sol = 0;

    for (int i = 0; i <= lungSol; i++) {
        sol[i] = initVal;
    }

    int i = 1;
    while (i >= 1) {
        bool valid = false;

        while (!valid && sol[i] <= max) {
            sol[i] += val;
            valid = validare(sol, lungSol, initVal);
        }

        if (sol[i] <= max) {
            if (i == lungSol) {
                printf("Permutare #%d - ", ++nr_sol);
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
    int v[3] = {1, 2, 3};   // Multimea de permutat
    int n = 3;

    int lungSol = n, max = n, initVal = 0, val = 1;
    int *sol = calloc(lungSol + 1, sizeof(int));

    permutari_backtrack(sol, lungSol, initVal, val, max);

    return 0;
}