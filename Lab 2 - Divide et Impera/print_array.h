#include <stdio.h>

void print_array(int *array, int nr) {
    printf("Array:");

    for (int i = 0; i < nr; i++) {
        printf(" %d", array[i]);
    }
    
    printf("\n");
}