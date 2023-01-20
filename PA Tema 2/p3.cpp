#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <iostream>

using namespace std;

// Reprezentarea grafului
typedef struct Graph {
    int nrNodes;    // Numarul nodurilor
    int **adjMat;   // Matricea de adiacente
} Graph;

#define INF 999999  // Valoarea considerata infinit

// Algoritmul Floyd-Warshall pentru gasirea distantelor intre toate nodurile
// unui graf.
int** floyd_warshall(Graph *graph) {
    // Vectorul de distante/costuri.
    // dist[u][v] = costul drumului de la u la v (se considera INF daca nu
    // exista drum intre u si v)
    int **dist = (int **) malloc((graph->nrNodes + 1) * sizeof(int *));
    for (int i = 0; i <= graph->nrNodes; i++) {
        dist[i] = (int *) calloc(graph->nrNodes + 1, sizeof(int));
    }

    // Initializeaza vectorul de distante cu INF pt muchii inexistente si
    // costurile muchiilor in rest
    for (int u = 1; u <= graph->nrNodes; u++) {
        for (int v = 1; v <= graph->nrNodes; v++) {
            if (u != v) {
                if (graph->adjMat[u][v] == 0) {
                    dist[u][v] = INF;
                } else {
                    dist[u][v] = graph->adjMat[u][v];
                }
            }
        }
    }

    // Pentru toate perechile (u, v), calculeaza costul drumului folosind
    // un nod intermediar k
    for (int k = 1; k <= graph->nrNodes; k++) {
        for (int u = 1; u <= graph->nrNodes; u++) {
            for (int v = 1; v <= graph->nrNodes; v++) {
                if (dist[u][v] >= dist[u][k] + dist[k][v]) {
                    dist[u][v] = dist[u][k] + dist[k][v];
                }
            }
        }
    }

    return dist;
}

// Parcurge toate perechile (u, v), calculand minimul sumei dintre costul
// drumului (u, v) si cel al drumului (v, u).
// Daca nu exista drumul (u, v), costul va fi INF, deci nu este problematic
// pentru algoritm. Altfel, suma va intoarce exact costul ciclului care
// incepe din u.
int get_minimum_cycle(Graph *graph, int **dist) {
    int min = INF;

    for (int u = 1; u <= graph->nrNodes; u++) {
        for (int v = 1; v <= graph->nrNodes; v++) {
            if (u != v) {
                if (dist[u][v] + dist[v][u] < min) {
                    min = dist[u][v] + dist[v][u];
                }
            }
        }
    }

    return min;
}

int main() {
    int nrNodes, nrEdges;
    int src, dest, weight;
    Graph graph;

	FILE* in = fopen("p3.in", "r");
    FILE* out = fopen("p3.out", "w");

    fscanf(in, "%d %d\n", &nrNodes, &nrEdges);

    // Creeaza un graf gol
    graph.nrNodes = nrNodes;
    graph.adjMat = (int **) malloc((nrNodes + 1) * sizeof(int *));
    for (int i = 0; i <= nrNodes; i++) {
		graph.adjMat[i] = (int *) calloc((nrNodes + 1), sizeof(int));
	}

    // Actualizeaza matricea de adiacente
	for (int i = 0; i < nrEdges; i++) {
		fscanf(in, "%d %d %d\n", &src, &dest, &weight);
        graph.adjMat[src][dest] = weight;
	}

    // Aplica algoritmul Floyd-Warshall pentru a gasi distantele intre toate
    // nodurile din graf
    int **dist = floyd_warshall(&graph);

    // Avand toate distantele, calculeaza ciclul de cost minim
    int min = get_minimum_cycle(&graph, dist);

    fprintf(out, "%d\n", min);

    return 0;
}
