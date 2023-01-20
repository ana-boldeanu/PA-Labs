#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Lab 7 - Grafuri Parcurgeri/graph.c"

void top_explore(int src, Graph* graph, char* color, Stack* topology) {
    color[src] = 'G';

    Node *succesor = graph->adList[src];
	while (succesor != NULL) {
		if (color[succesor->val] == 'A') {
			top_explore(succesor->val, graph, color, topology);
		}
		succesor = succesor->next;
	}

	color[src] = 'N';
    push(topology, src);
}

void topological_sort(Graph* graph) {
	char *color = calloc(graph->nrNodes, sizeof(char));
    for (int i = 0; i < graph->nrNodes; i++) {
        color[i] = 'A';
    }

	Stack *topology = createList();

	for (int i = graph->nrNodes - 1; i >= 0; i--) {
		if (color[i] == 'A') {
			top_explore(i, graph, color, topology);
		}
	}

	printf("Sortare topologica:\n    ");
	while(!isStackEmpty(topology)) {
		printf("%c ", top(topology) + 65);
		pop(topology);
	}
    printf("\n");
}

int main() {
	FILE *in = fopen("top_graph.in", "r");

	int nrNodes;
	fscanf(in, "%d\n", &nrNodes);

	Graph *graph1 = createGraphAdjList(nrNodes);

	for (int i = 0; i < nrNodes; i++) {
		char line[100];
		fgets(line, sizeof(line), in);
		// Remove trailing newline
		line[strlen(line) - 2] = 0;
		char *token = strtok(line, " ");

		if (token == NULL) {
			graph1->adList[i] = NULL;
		}

		while (token != NULL) {
			int successor = atoi(token);
			addEdgeList(graph1, i, successor);
			token = strtok(NULL, " ");
		}
	}
	
	topological_sort(graph1);	

    return 0;
}