#include <stdio.h>
#include "print_array.h"

int find_max(int array[], int start, int stop) {
    if (start == stop) {
        return array[start];
    }

    int mid = (start + stop) / 2;

    int left = find_max(array, start, mid);
    int right = find_max(array, mid + 1, stop);

    if (left > right) {
        return left;
    }
    return right;
}

int main() {
    int v[5] = {1, 3, 2, 7, 4};
    int size = 5;

    print_array(v, size);
    int max = find_max(v, 0, size - 1);

    printf("Max: %d\n", max);

    return 0;
}