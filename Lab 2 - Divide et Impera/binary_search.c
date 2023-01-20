#include <stdio.h>
#include "print_array.h"

int binary_search(int *array, int x, int start, int stop) {
    if (start > stop) {
        return -1;
    }

    int mid = (start + stop) / 2;

    if (array[mid] == x) {
        return mid;

    } else if (array[mid] < x) {
        return binary_search(array, x, mid + 1, stop);

    } else if (array[mid] > x) {
        return binary_search(array, x, start, mid - 1);
    }

    return -1;
}

int main() {
    int v[5] = {1, 2, 3, 5, 7};
    int size = 5;
    int x = 5;

    print_array(v, size);
    int pos = binary_search(v, x, 0, size - 1);

    printf("%d is on position %d\n", x, pos);

    return 0;
}