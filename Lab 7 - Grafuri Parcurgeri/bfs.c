#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "graph.c"

int time; int step = 1;

void bfs_iterative(Graph* graph, int src) {
    printf("\nBFS incepand din nodul %c\n\n", src + 65);
	
    int *d = calloc(graph->nrNodes, sizeof(int));
	int *f = calloc(graph->nrNodes, sizeof(int));
    int *parent = calloc(graph->nrNodes, sizeof(int));
	char *color = calloc(graph->nrNodes, sizeof(char));
    for (int i = 0; i < graph->nrNodes; i++) {
        parent[i] = -1;
        d[i] = INT_MAX;
        color[i] = 'A';
    }

    Queue* queue = createQueue();
    d[src] = 0;
    color[src] = 'G';
    enqueue(queue, src);

    printf("Pasul %d:\n", step++);
    
	printf("    d(%c) = %2d | c(%c) = %c | p(%c) = null\n    ", src + 65, d[src], src + 65, color[src], src + 65);
    printQueue(&queue);

	while(!isQueueEmpty(queue)) {
		int node = front(queue);
		dequeue(queue);

        printf("\nPasul %d:\n", step++);
			
		Node *successor = graph->adList[node];

		while (successor != NULL) {
            int succ = successor->val;

			if (color[succ] == 'A') {
                // Vizitare succesori
				d[succ] = d[node] + 1;
				color[succ] = 'G';
				parent[succ] = node;

                enqueue(queue, succ);
                printf("    d(%c) = %2d | c(%c) = %c | p(%c) = %c\n", succ + 65, d[succ], succ + 65, color[succ], succ + 65, parent[succ] + 65);
			}

			successor = successor->next;
		}

		color[node] = 'N';
		printf("    c(%c) = %c\n", node + 65, color[node]);

        printf("    "); printQueue(&queue);
	}

	destroyQueue(queue);
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

	bfs_iterative(graph, 0);

	return 0;
}