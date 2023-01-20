#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void print_sol(int *v, int n) {
    for (int i = 1; i <= n; i++) {
        if (v[i] == 1) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

bool validare(int *v, int lungSol, int initVal) {
    return true;
}

void submultimi_backtrack(int *sol, int lungSol, int initVal, int val, int max) {
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
                printf("Submultime #%d - ", ++nr_sol);
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
    int v[3] = {1, 2, 3};   // Multimea data
    int n = 3;

    int lungSol = n, max = 1, initVal = -1, val = 1;
    int *sol = calloc(lungSol + 1, sizeof(int));

    submultimi_backtrack(sol, lungSol, initVal, val, max);

    return 0;
}