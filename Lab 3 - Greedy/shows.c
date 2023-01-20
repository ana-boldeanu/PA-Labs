#include <stdio.h>
#include <stdlib.h>

int get_shows(int *start_times, int *end_times, int nr) {
    int last_stop = 0;
    int nr_shows = 0;

    for (int i = 0; i < nr; i++) {
        if (start_times[i] >= last_stop) {
            nr_shows++;
            printf("Show #%d starts at %d, ends at %d\n", nr_shows, start_times[i], end_times[i]);
            last_stop = end_times[i];
        }
    }

    return nr_shows;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
 
void bubble_sort_shows(int *start_times, int *end_times, int nr) {
   for (int i = 0; i < nr - 1; i++) {
       for (int j = 0; j < nr - i - 1; j++) {
           if (end_times[j] > end_times[j + 1]) {
               swap(&end_times[j], &end_times[j + 1]);
               swap(&start_times[j], &start_times[j + 1]);
           }
       }
   }
}

int main() {
    int start_times[6] = {10, 11, 12, 14, 16, 17};
    int end_times[6] = {11, 13, 13, 18, 17, 19};
    int total = 6;

    bubble_sort_shows(start_times, end_times, total);

    int max_shows = get_shows(start_times, end_times, total);
    printf("Max number of shows = %d\n", max_shows);

    return 0;
}