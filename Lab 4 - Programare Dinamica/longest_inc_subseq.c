#include <stdio.h>
#include <stdlib.h>
#include "../Lab 2 - Divide et Impera/print_array.h"

/*
    Fiind dat un sir de nr. naturale, sa se gaseasca cel mai lung subsir crescator

    D[i] = lungimea subsirului crescator de lungime maxima, folosind elementele de pe
        pozitiile 0 .. i
    
    D[i] = max(D[j]) + 1 , pentru j < i && v[j] < v[i]
 */
int *longest_inc_subseq(int *arr, int size) {
    // Construirea vectorului de solutii intermediare
    int *D = calloc(size + 1, sizeof(int));

    // Caz de baza (subsir format din primul element)
    D[0] = 1;

    for (int i = 1; i < size; i++) {
        int max = 0;
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && D[j] > max) {
                max = D[j];
            }
        }
        D[i] = max + 1;
    }

    return D;
}

int *get_longest_inc_subseq(int *D, int *arr, int size) {
    int *subseq = calloc(D[size - 1], sizeof(int));
    int k = 0, max = 0;

    for (int i = 0; i < size; i++) {
        if (D[i] > max) {
            // Inseamna ca elementul curent a fost adaugat in subsirul maxim
            subseq[k] = arr[i];
            k++;

            max = D[i];     // Actualizarea lungimii maxime
            
        } else if (D[i] == max) {
            subseq[k - 1] = arr[i];
        }
    }
    
    return subseq;
}


int main() {
    int array[8] = {1, 2, 9, 3, 8, 4, 0, 7};
    int size = 8;

    // Construirea vectorului de solutii
    int *D = longest_inc_subseq(array, size);

    print_array(array, size);
    printf("Lungimea celui mai lung subsir este %d\n", D[size - 1]);

    // Determinarea elementelor ce compun solutia
    int *subseq = get_longest_inc_subseq(D, array, size);
    print_array(subseq, D[size - 1]);

    return 0;
}

