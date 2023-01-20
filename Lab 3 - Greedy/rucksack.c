#include <stdio.h>
#include <stdlib.h>

typedef struct Object {
    int index;
    double weight;
    double value;
    double pondere;
} Object;

void compute_vals(Object *objects, int nr) {
    for (int i = 0; i < nr; i++) {
        objects[i].pondere = objects[i].value / objects[i].weight;
    }
}

void insertion_sort(Object *objects, int nr) {
    for (int i = 1; i < nr; i++) {
        Object key = objects[i];
        int j = i - 1;

        while (j >= 0 && objects[j].pondere < key.pondere) {
            objects[j + 1] = objects[j];
            j--;
        }

        objects[j + 1] = key;
    }
}

void rucksack_continuous(Object *objects, int nr_obj, double max_weight) {
    double curr_weight = 0;
    double curr_value = 0;
    
    for (int i = 0; i < nr_obj; i++) {
        if (objects[i].weight + curr_weight <= max_weight) {
            printf("Added object %d of weight %f, value %f\n", 
                        objects[i].index, objects[i].weight, objects[i].value);
            curr_weight += objects[i].weight;
            curr_value += objects[i].value;

        } else {
            double remainder_weight = max_weight - curr_weight;
            double obj_fraction = remainder_weight / objects[i].weight;

            printf("Added fraction %f of object %d, value %f\n", 
                        obj_fraction, objects[i].index, obj_fraction * objects[i].value);
            curr_value += obj_fraction * objects[i].value;

            printf("Total value: %f\n", curr_value);
        }
    }
}

int main() {
    // Rucksack
    double max_weight = 50;

    // Objects
    int nr_obj = 3;
    Object obj1; obj1.index = 1; obj1.weight = 10; obj1.value = 60;
    Object obj2; obj2.index = 2; obj2.weight = 30; obj2.value = 120;
    Object obj3; obj3.index = 3; obj3.weight = 20; obj3.value = 100;

    Object *objects = calloc(nr_obj, sizeof(struct Object));
    objects[0] = obj1;
    objects[1] = obj2;
    objects[2] = obj3;

    // Calculeaza ponderile obiectelor
    compute_vals(objects, nr_obj);

    // Sorteaza obiectele crescator in functie de pondere
    insertion_sort(objects, nr_obj);

    // Alege obiectele care incap in rucsac
    rucksack_continuous(objects, nr_obj, max_weight);

    return 0;
}





// Printing array of Objects
void print_obj(Object *objects, int nr) {
    printf("Objects list:\n");
    for (int i = 0; i < nr; i++) {
        printf("~ object %d of weight %f, value %f, pondere%f\n", 
                objects[i].index, objects[i].weight, objects[i].value, objects[i].pondere);
    }
    printf("\n");
}