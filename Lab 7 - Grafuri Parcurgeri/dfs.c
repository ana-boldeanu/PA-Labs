#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.c"

int time; int step = 1;

void dfs_explore(int src, Graph* graph, char *color, int *d, int *f, int *parent) {
	time++;
	d[src] = time;
	color[src] = 'G';
	
    if (src == 0) {
        printf("%2d. c(%c) = %c  |  d(%c) = %2d  |  p(%c) = null\n", step++, src + 65, color[src], src + 65, d[src], src + 65);
    } else {
        printf("%2d. c(%c) = %c  |  d(%c) = %2d  |  p(%c) = %c\n", step++, src + 65, color[src], src + 65, d[src], src + 65, parent[src] + 65);
    }

    Node *succesor = graph->adList[src];
	while (succesor != NULL) {
		if (color[succesor->val] == 'A') {
			parent[succesor->val] = src;
			dfs_explore(succesor->val, graph, color, d, f, parent);
		}
		succesor = succesor->next;
	}

	time++;
	f[src] = time;  
	color[src] = 'N';

	printf("%2d. c(%c) = %c  |  f(%c) = %2d\n", step++, src + 65, color[src], src + 65, f[src]);
}

void dfs_recursive(Graph* graph) {
    printf("\nParcurgere DFS, incepand din A\n\n");

	int *d = calloc(graph->nrNodes, sizeof(int));
	int *f = calloc(graph->nrNodes, sizeof(int));
    int *parent = calloc(graph->nrNodes, sizeof(int));
	char *color = calloc(graph->nrNodes, sizeof(char));
    for (int i = 0; i < graph->nrNodes; i++) {
        color[i] = 'A';
    }

	for (int i = 0; i < graph->nrNodes; i++){
		if (color[i] == 'A') {
            dfs_explore(i, graph, color, d, f, parent);
        }
	}
	
	free(color); free(graph);
}

int main() {
	FILE *in = fopen("graph.in", "r");

	int nrNodes;
	fscanf(in, "%d\n", &nrNodes);

	Graph *graph = createGraphAdjList(nrNodes);

	for (int i = 0; i < nrNodes; i++) {
		char line[100];
		fgets(line, sizeof(line), in);
		// Remove trailing newline
		line[strlen(line) - 2] = 0;
		char *token = strtok(line, " ");

		while (token != NULL) {
			int successor = atoi(token);
			addEdgeList(graph, i, successor);
			token = strtok(NULL, " \n");
		}
	}

	dfs_recursive(graph);

	return 0;
}