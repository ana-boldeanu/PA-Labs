#include <stdio.h>
#include <stdlib.h>

int max(double a, double b) { return a > b ? a : b; }

/*
    Problema Rucsacului Discret

    D[i][j] = val. optima din rucsac, considerand obiectele de la 1 la i
        unde j reprezinta capacitatea ramasa in rucsac

    D[i][j] = max(D[i - 1][j], D[i - 1][j - m_i] + v_i)

    Solutia finala este D[nr_obj][max_weight]   // in ex. D[3][50]
*/
double **rucksack_dynamic(int max_weight, int nr_obj, int *weights, double *values) {
    // Alocarea matricei de solutii partiale D[i][j]
    double **D = calloc(nr_obj + 1, sizeof(*D));
    for (int i = 0; i <= nr_obj; i++) {
        D[i] = calloc(max_weight + 1, sizeof(**D));
    }

    // Completarea matricei de solutii
    for (int i = 0; i <= nr_obj; i++) {      // Caz de baza, 0 capacitate ramasa
        D[i][0] = 0;
    }
    for (int j = 0; j <= max_weight; j++) {
        D[0][j] = 0;                        // Caz de baza, 0 obiecte considerate
    }

    for (int i = 1; i <= nr_obj; i++) {
        for (int j = 1; j <= max_weight; j++) {
            if (weights[i] <= j) {
                // Se poate adauga un obiect
                double add_i =  D[i - 1][j - weights[i]] + values[i];
                double do_not_add_i = D[i - 1][j];
                
                D[i][j] = max(do_not_add_i, add_i);

            } else {
                D[i][j] = -1;   
            }
        }
    }

    return D;
}

void get_objects(double **D, int max_weight, int nr_obj, int *weights, double *values) {
    for (int i = nr_obj; i >= 1; i--) {
        for (int j = max_weight; j >= 1; j--) {
            // Verifica daca a fost adaugat obiectul curent
            double add_i =  D[i - 1][j - weights[i]] + values[i];
            double do_not_add_i = D[i - 1][j];

            if (add_i > do_not_add_i) {
                printf("Adaugat obiectul #%d, masa = %d, val = %.2f\n", i, weights[i], values[i]);
                j -= weights[i];
            }

            i -= 1;
        }
    }
}

int main() {
    // Rucksack
    int max_weight = 50;

    // Obiecte
    int nr_obj = 3;
    int weights[4] = {0, 10, 30, 20};       // Restrictie: doar greutati numere intregi
    double values[4] = {0, 60, 120, 100};

    // Construieste matricea solutiilor
    double **D = rucksack_dynamic(max_weight, nr_obj, weights, values);

    // Verifica ce obiecte au facut parte din solutie
    get_objects(D, max_weight, nr_obj, weights, values);

    printf("Valoare maxima din rucsac = %.2f\n", D[nr_obj][max_weight]);

    return 0;
}