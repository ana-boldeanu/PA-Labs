#include <stdio.h>
#include "print_array.h"

int nr_occurences(int *array, int x, int start, int stop) {
    if (start == stop) {
        if (array[start] == x) {
            return 1;
        }
        return 0;
    }

    int mid = (start + stop) / 2;

    int left = nr_occurences(array, x, start, mid);
    int right = nr_occurences(array, x, mid + 1, stop);

    return left + right;
}

int main() {
    int v[7] = {3, 1, 2, 3, 3, 4, 3};
    int size = 7;
    int x = 3;

    print_array(v, size);
    int nr_occ = nr_occurences(v, x, 0, size - 1);

    printf("%d has %d occurences\n", x, nr_occ);

    return 0;
}