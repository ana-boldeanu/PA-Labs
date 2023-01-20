#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

typedef struct Edge {
    int src, dest, weight;
} Edge;

typedef struct Graph {
    int V;      	// Vertices
    int E;     	 	// Edges
    Edge *edge;     // Adjacency List
} Graph;

void create_graph(Graph* G, int V, int E) {
	G->V = V;
	G->E = E;
	G->edge = malloc(E * sizeof(Edge));
}

void bellman_ford(Graph G, int s) {
    int V = G.V;
	int E = G.E;
	int distance[V];
	int parents[V];
	int visited[V];

	// Initializari noduri
	for (int i = 0; i < V; i++) {
		distance[i] = INT_MAX;
		parents[i] = -1;
		visited[i] = 0;
	}
	distance[s] = 0;

	// i = lungimea drumui considerat
	for (int i = 1; i < V; i++) {
		printf("i = %d. ", i);
		printf("Arce relaxate:\n");

		// Itereaza prin toate muchiile din graf
		for (int j = 0; j < E; j++) {
			int u = G.edge[j].src;
			int v = G.edge[j].dest;
			int weight = G.edge[j].weight;

			if (!visited[v] && distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
				// Arcul (u, v) a fost relaxat
				printf("(%d, %d) ", u+1, v+1);

				// Actualizeaza costurile
				distance[v] = distance[u] + weight;
				parents[v] = u;
				visited[v] = 1;

				printf("  Update d(%d) = %2d | p(%d) = %d\n", v+1, distance[v], v+1, parents[v]+1);
			}
		}

		for (int i = 0; i < E; i++) {
			visited[i] = 0;
		}

		printf("\n");
	}

	// Verifica daca exista ciclu negativ
	for (int i = 0; i < E; i++) {
		int u = G.edge[i].src;
		int v = G.edge[i].dest;
		int weight = G.edge[i].weight;
		if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
			printf("Graph contains negative weight cycle\n");
			return;
		}
	}
}

int main(int argc, char **argv) {
	int V, E, start;
	Graph G;

	FILE* in = freopen("in", "r", stdin);
		
	scanf ("%d %d %d", &V, &E, &start);
	create_graph(&G, V, E);

	for (int j = 0; j < E; j++) {
		scanf("%d ", &G.edge[j].src);
		scanf("%d ", &G.edge[j].dest);
		scanf("%d ", &G.edge[j].weight);
	}
	
	// Bellman_Ford(1);
	bellman_ford(G,start);

	free(G.edge);

    return 0;
}