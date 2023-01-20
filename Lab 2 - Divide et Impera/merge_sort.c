#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "print_array.h"

void merge(int *array, int start, int mid, int stop) {
    int size_left = mid - start + 1;
    int size_right = stop - mid;

    // Creeaza vectorii cu elementele din stanga si dreapta
    int *left_array = calloc(size_left + 1, sizeof(int));
    int *right_array = calloc(size_right + 1, sizeof(int));

    // Copiaza elementele in cei doi vectori
    for (int i = 0; i < size_left; i++) {
        left_array[i] = array[start + i];
    }
    for (int i = 0; i < size_right; i++) {
        right_array[i] = array[mid + i + 1];
    }

    // Dummy pentru ultimul element
    left_array[size_left] = INT_MAX;
    right_array[size_right] = INT_MAX;

    // Interclaseaza vectorii
    int i = 0, j = 0;
    for (int k = start; k <= stop; k++) {
        if (left_array[i] <= right_array[j]) {
            array[k] = left_array[i];
            i++;

        } else {
            array[k] = right_array[j];
            j++;
        }
    }

    free(left_array);
    free(right_array);
}

void merge_sort(int *array, int start, int stop) {
    if (start < stop) {
        int mid = (start + stop) / 2;

        merge_sort(array, start, mid);
        merge_sort(array, mid + 1, stop);

        merge(array, start, mid, stop);
    }
}

int main() {
    int v[6] = {2, 1, 7, 3, 4, 0};
    int size = 6;

    print_array(v, size);

    merge_sort(v, 0, size - 1);
    
    printf("Sorted\n");
    print_array(v, size);

    return 0;
}