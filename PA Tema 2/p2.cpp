#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

#define N 10001

typedef struct Graph {
    int nrNodes;
    list<int> *adjLists;
} Graph;

int main() {
    Graph *graph = (Graph *) calloc(1, sizeof(Graph));
    graph->adjLists = new list<int>[N];
}
