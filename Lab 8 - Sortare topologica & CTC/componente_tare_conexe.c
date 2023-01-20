#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.c"

int time; int step = 1; int CTC_count;

typedef struct node {
    int val;
    int f;
} node;

void dfs_2_explore(int src, Graph* graph, char *color, int *d, int *f, int *parent, int *f_first) {
	time++;
	d[src] = time;
	color[src] = 'G';
	
	printf("%c ", src + 65);

	// Selecteaza succesorul dintre vecini, cu f maxim
	int found = 0;
    Node *succesor = graph->adList[src];
	Node *max_successor = graph->adList[src];
	while (succesor != NULL) {
		if (color[succesor->val] == 'A') {
			found = 1;
			if (f_first[succesor->val] > f_first[max_successor->val]) {
				max_successor = succesor;
			}	
		}
		succesor = succesor->next;
	}
	succesor = max_successor;

	if (found == 0) {
		printf("\nCTC #%d: ", ++CTC_count);
	}

	// Exploreaza succesorul
	while (succesor != NULL) {
		if (color[succesor->val] == 'A') {
			parent[succesor->val] = src;
			dfs_2_explore(succesor->val, graph, color, d, f, parent, f_first);
		}
		succesor = succesor->next;
	}

	time++;
	f[src] = time;  
	color[src] = 'N';
}

int* dfs_2(Graph* graph, node* sorted_nodes, int *f_first) {
    printf("A doua parcurgere DFS, dupa f:\n\n");

	int *d = calloc(graph->nrNodes, sizeof(int));
	int *f = calloc(graph->nrNodes, sizeof(int));
    int *parent = calloc(graph->nrNodes, sizeof(int));
	char *color = calloc(graph->nrNodes, sizeof(char));
    for (int i = 0; i < graph->nrNodes; i++) {
        color[i] = 'A';
    }

	printf("CTC #%d: ", ++CTC_count);
	for (int i = 0; i < graph->nrNodes; i++){
		if (color[sorted_nodes[i].val] == 'A') {
            dfs_2_explore(sorted_nodes[i].val, graph, color, d, f, parent, f_first);
        }
	}

	// printf("\n\n");
    // for (int i = 0; i < graph->nrNodes; i++) {
    //     printf("%c -> d = %2d, f = %2d\n", sorted_nodes[i].val + 65, d[sorted_nodes[i].val], f[sorted_nodes[i].val]);
    // }

    return f;
}

void dfs_1_explore(int src, Graph* graph, char *color, int *d, int *f, int *parent) {
	time++;
	d[src] = time;
	color[src] = 'G';

    Node *succesor = graph->adList[src];
	while (succesor != NULL) {
		if (color[succesor->val] == 'A') {
			parent[succesor->val] = src;
			dfs_1_explore(succesor->val, graph, color, d, f, parent);
		}
		succesor = succesor->next;
	}

	time++;
	f[src] = time;  
	color[src] = 'N';
}

int* dfs_1(Graph* graph) {
    printf("Prima parcurgere DFS, alfabetic:\n\n");

	int *d = calloc(graph->nrNodes, sizeof(int));
	int *f = calloc(graph->nrNodes, sizeof(int));
    int *parent = calloc(graph->nrNodes, sizeof(int));
	char *color = calloc(graph->nrNodes, sizeof(char));
    for (int i = 0; i < graph->nrNodes; i++) {
        color[i] = 'A';
    }

	for (int i = 0; i < graph->nrNodes; i++){
		if (color[i] == 'A') {
            dfs_1_explore(i, graph, color, d, f, parent);
        }
	}

    for (int i = 0; i < graph->nrNodes; i++) {
        printf("%c -> d = %2d, f = %2d\n", i + 65, d[i], f[i]);
    }

    return f;
}

void insertion_sort_by_f(node *nodes, int nr) {
    for (int i = 1; i < nr; i++) {
        node key = nodes[i];
        int j = i - 1;

        while (j >= 0 && nodes[j].f < key.f) {
            nodes[j + 1] = nodes[j];
            j--;
        }

        nodes[j + 1] = key;
    }
}

void kosaraju(Graph *graph, Graph *graph_t) {
    // Primul DFS
    int *f = dfs_1(graph);

    // Sorteaza nodurile dupa f, descrescator
    node *sorted_nodes = calloc(graph->nrNodes, sizeof(node));
    for (int i = 0; i < graph->nrNodes; i++) {
        node new_node;
        new_node.val = i;
        new_node.f = f[i];
        sorted_nodes[i] = new_node;
    }

    insertion_sort_by_f(sorted_nodes, graph->nrNodes);

    printf("\nOrdinea nodurilor dupa valoarea f:\n\n");
    for (int i = 0; i < graph->nrNodes; i++) {
        printf("%c ", sorted_nodes[i].val + 65);
    }
    printf("\n\n");

    // A doua parcurgere, dupa ordinea descrescatoare pentru f
    time = 0; step = 1;
    dfs_2(graph_t, sorted_nodes, f);
}


int main() {
	FILE *in = fopen("ctc_graph.in", "r");

	int nrNodes;
	fscanf(in, "%d\n", &nrNodes);

	Graph *graph = createGraphAdjList(nrNodes);
    Graph *graph_t = createGraphAdjList(nrNodes);

	for (int i = 0; i < nrNodes; i++) {
		char line[100];
		fgets(line, sizeof(line), in);
		// Remove trailing newline
		line[strlen(line) - 2] = 0;
		char *token = strtok(line, " ");

		if (token == NULL) {
			graph->adList[i] = NULL;
		}

		while (token != NULL) {
			int successor = atoi(token);

			addEdgeList(graph, i, successor);
            addEdgeList(graph_t, successor, i);

			token = strtok(NULL, " ");
		}
	}
	
	kosaraju(graph, graph_t);	

    return 0;
}