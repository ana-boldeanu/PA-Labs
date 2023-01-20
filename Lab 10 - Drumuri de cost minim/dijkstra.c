#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#include "heap.h"

typedef struct Edge {
    int dest, weight;
    struct Edge *next;
} Edge;

typedef struct Graph {
    int V;     		// Vertices
    Edge **adl;     // Adjacency List
} Graph;

void alloc_list(Graph *G, int n) {
    G->V = n;
    G->adl = malloc((n+1) * sizeof(Edge*));
    for(int i = 0; i < n; i++)
		G->adl[i] = NULL;
}

void free_list(Graph *G) {
    Edge* it;
    for(int i = 0; i < G->V; i++) {
		it = G->adl[i];
		while(it != NULL) {
			Edge* aux = it;
			it = it->next;
			free(aux);
		}
		G->adl[i] = NULL;
	}
	G->V = 0;
	free(G->adl);
}

void insert_edge(Graph *G, int src, int dest, int w) {
    Edge *t;
    t = (Edge*) malloc(sizeof(Edge));
    t->dest = dest; 
    t->weight = w; 
    t->next = G->adl[src]; 
    G->adl[src] = t;
}


void dijkstra(Graph G, int s) {
	int parents[G.V];

	// Initializeaza coada de prioritati
    MinHeap* h = newQueue(G.V);
	h->size = G.V;

	// Adauga toate nodurile in coada
	MinHeapNode* node;
	for (int i = 0; i < G.V; i++) {
		if (i == s) {
			node = newNode(i, 0);			// d(s) = 0
		} else {
			node = newNode(i, INT_MAX);		// d(u) = INF, u != s
		}

		h->elem[i] = node;
		h->pos[i] = i;
		parents[i] = -1;
	}

	siftUp(h, h->elem[s]->v, h->elem[s]->d);

	int step = 1;
	// Cat timp mai sunt noduri in coada de prioritati
	while (!isEmpty(h)) {
		printf("Pas %d.\n", step++);

		// Extrage nodul cu d minim
		MinHeapNode* u = removeMin(h);
		printf("  Extrage %d | d(%d) = %d | p(%d) = %d\n", u->v+1, u->v+1, u->d, u->v+1, parents[u->v]+1);

		// Actualizeaza costurile pt fiecare succesor al lui u
		for (Edge* edge = G.adl[u->v]; edge != NULL; edge = edge->next) {
			int succ = edge->dest;
			if (isInMinHeap(h, succ)) {
				// Daca d(u) + w(u,v) < d(v)
				if (u->d + edge->weight < h->elem[h->pos[succ]]->d) {
					// Actualizeaza costul d(v)
					h->elem[h->pos[succ]]->d = u->d + edge->weight;

					// Actualizeaza coada de prioritati
					siftUp(h, h->elem[h->pos[succ]]->v, h->elem[h->pos[succ]]->d);

					// Actualizeaza parintele lui v
					parents[h->elem[h->pos[succ]]->v] = u->v;
					printf("  Update p(%d) = %d\n", succ+1, parents[succ]+1);
				}
			}
		}
		printf("\n");
		free(u);
	}
	freeQueue(h);
}


int main(int argc, char **argv) {
    int src, dest, weight;
	int V, E, start;
	Graph G;

	FILE* in = freopen("in", "r", stdin);

    scanf ("%d %d %d", &V, &E, &start);
	alloc_list(&G, V);

	for (int j = 0; j < E; j++) {
		scanf("%d %d %d", &src, &dest, &weight);
	    insert_edge(&G,src,dest,weight);
	}
		
	dijkstra(G,start);
	free_list(&G);
	
	return 0;
}