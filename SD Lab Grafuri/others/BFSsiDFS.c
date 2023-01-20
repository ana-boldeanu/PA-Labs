#include "Util.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NEI 26
#define INF 999

typedef struct Node {
	char letter;
	int dist;
	char color;
	struct Node *parent;
	char *nei;
	int final;
}Node;

int freeNode(Node* n) {
	free(n->nei);
	free(n);
}

Node* allocNode() {
	Node *output = calloc(1, sizeof(Node));

	output->parent = NULL;
	output->nei = calloc(MAX_NEI, sizeof(char));
	output->color = 'a';
	return output;
}

Queue* printQueue(Queue* q) {
	Queue* newq = createQueue();
	printf("Q{ ");
	while(!isQueueEmpty(q)) {
		enqueue(newq, front(q));
		printf("%c ",(char)(front(q) + 'A'));
		dequeue(q);
	}
	printf("}\n");
	destroyQueue(q);
	return newq;
}

void BFS(Node* s, Node** graph, int n) {
	// Init
	for(int i = 0; i < n; i++) {
		graph[i]->parent = NULL;
		graph[i]->dist = INF;
		graph[i]->color = 'a';
	}
	Queue* q = createQueue();
	s->dist = 0;
	enqueue(q, s->letter - 'A');
	s->color = 'g';

	printf("dist(%c) = %d | ", s->letter, 0);
	printf("p(%c) = null | ", s->letter);
	printf("c(%c) = gri\n", s->letter);
	q = printQueue(q);

	while(!isQueueEmpty(q)) {
		int u = front(q);
		Node* currentNode = graph[u];
		for(int i = 0; i < strlen(currentNode->nei); i++) {
			if(graph[currentNode->nei[i] - 'A']->color == 'a') {
				graph[currentNode->nei[i] - 'A']->color = 'g';
				graph[currentNode->nei[i] - 'A']->dist = currentNode->dist + 1;
				graph[currentNode->nei[i] - 'A']->parent = currentNode;
				enqueue(q, currentNode->nei[i] - 'A');
				printf("dist(%c) = %d | ", currentNode->nei[i], currentNode->dist + 1);
				printf("p(%c) = %c | ", currentNode->nei[i], currentNode->letter);
				printf("c(%c) = gri\n", currentNode->nei[i]);
			}
		}
		currentNode->color = 'n';
		printf("c(%c) = negru\n", currentNode->letter);
		dequeue(q);
		q = printQueue(q);
	}
	destroyQueue(q);
}

int t;

void explore(Node* node, int n, Node** graph) {
	node->dist = ++t;
	node->color = 'g';
	printf("c(%c) = gri | ", node->letter);
	printf("d(%c) = %d \n", node->letter, node->dist);

	for(int i = 0; i < strlen(node->nei); i++) {
		if(graph[node->nei[i] - 'A']->color == 'a') {
			graph[node->nei[i] - 'A']->parent = node;
			printf("p(%c) = %c \n\n", graph[node->nei[i] - 'A']->letter, graph[node->nei[i] - 'A']->parent->letter);
			explore(graph[node->nei[i] - 'A'], n, graph);
		}
	}
	node->color = 'n';
	node->final = ++t;
	printf("c(%c) = negru | ", node->letter);
	printf("f(%c) = %d \n", node->letter, node->final);
}

void DFS(Node** graph, int n) {
	for(int i = 0; i < n; i++) {
		graph[i]->color = 'a';
		graph[i]->parent = NULL;
	}

	for(int i = 0; i < n; i++) {
		if(graph[i]->color == 'a') {
			explore(graph[i], n, graph);
		}
	}
}

int main()
{
	FILE *f = fopen("BFS.in", "r");

	int n;
	Node** v = calloc(20, sizeof(Node*));
	fscanf(f, "%d\n", &n);
	char currentLetter = 'A';

	for (int i = 0; i < n; i++) {

		v[i] = allocNode();
		v[i]->letter = currentLetter;
		++currentLetter;

		char line[100];
		fgets(line, sizeof(line), f);
		if(line == NULL) continue;
		// Remove trailing newline because fgets is a beauty.
		line[strlen(line) - 1] = 0;
		if(line == 0) v[i]->nei = NULL;
		else strncpy(v[i]->nei, line, strlen(line));
	}

	//BFS(v[0], v, n);
	DFS(v, n);

	return 0;
}
