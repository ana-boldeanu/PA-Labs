#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Util.h"
#include "Graph.h"

TGraphL* createGraphAdjList(int numberOfNodes) {
	//TODO: 1
	TGraphL* graph = malloc(sizeof(TGraphL));
	graph->nn = numberOfNodes;
	graph->adl = malloc(numberOfNodes * sizeof(ATNode));
	for (int i=0; i<numberOfNodes; i++)
		graph->adl[i] = NULL;
	return graph;
}

void addEdgeList(TGraphL* graph, int v1, int v2) {
	//TODO: 1
	TNode* node1 = malloc(sizeof(TNode));
	node1->v = v1;
	node1->next = graph->adl[v2];
	graph->adl[v2] = node1;

	TNode* node2 = malloc(sizeof(TNode));
	node2->v = v2;
	node2->next = graph->adl[v1];
	graph->adl[v1] = node2;
}

List* dfsIterative(TGraphL* graph, int s) {
	//TODO: 2
	List* path = createList();
	Stack* stack = createStack();

	int* visited = malloc(graph->nn * sizeof(int));
	for (int i=0; i<graph->nn; i++)
		visited[i] = 0;
	
	push(stack, s);
	TNode* aux = graph->adl[s];
	
	while (isStackEmpty(stack) != 1) {
		s = top(stack);
		pop(stack);

		enqueue(path, s);
		visited[s] = 1;

		aux = graph->adl[s];
		while (aux != NULL) {
			if (visited[aux->v] == 0) {
				push(stack, aux->v);
				visited[aux->v] = 1;
			}
		aux = aux->next;
		}
	}
	free(visited);
	destroyStack(stack);
	return path;
}

void dfsRecHelper(TGraphL* graph, int* visited, List* path, int s) {
	//TODO: 3
	enqueue(path, s);
	visited[s] = 1;
	TNode* aux = graph->adl[s];

	while (aux != NULL) {
		if (visited[aux->v] == 0) {
			visited[aux->v] = 1;
			dfsRecHelper(graph, visited, path, aux->v);
		}
		aux = aux->next;
	}
}

List* dfsRecursive(TGraphL* graph, int s) {
	// TODO 3
	int* visited = malloc(graph->nn * sizeof(int));
	for (int i=0; i<graph->nn; i++)
		visited[i] = 0;
	List* path = createList();
	dfsRecHelper(graph, visited, path, s);

	free(visited);
	return path;
}

List* bfs(TGraphL* graph, int s){
	// TODO: 4
	List* path = createList();
	Queue* queue = createQueue();

	int* visited = malloc(graph->nn * sizeof(int));
	for (int i=0; i<graph->nn; i++)
		visited[i] = 0;
	
	push(queue, s);
	TNode* aux = graph->adl[s];
	
	while (isQueueEmpty(queue) != 1) {
		s = front(queue);
		dequeue(queue);

		enqueue(path, s);
		visited[s] = 1;

		aux = graph->adl[s];
		while (aux != NULL) {
			if (visited[aux->v] == 0) {
				enqueue(queue, aux->v);
				visited[aux->v] = 1;
			}
		aux = aux->next;
		}
	}
	free(visited);
	destroyQueue(queue);
	return path;

}


void destroyGraphAdjList(TGraphL* graph){
	// TODO: 5
	for (int i=0; i<graph->nn; i++)
		removeNodeList(graph, i);
	free(graph->adl);
	free(graph);
}

void removeEdgeList(TGraphL* graph, int v1, int v2){
	TNode* it = graph->adl[v1];
	TNode* prev = NULL;
	while(it != NULL && it->v != v2){
		prev = it;
		it = it->next;
	}

	if(it == NULL)return;

	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v1] = it->next;
	free(it);

	it = graph->adl[v2];
	prev = NULL;
	while(it != NULL && it->v != v1){
		prev = it;
		it = it->next;
	}
	if(it == NULL) return;
	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v2] = it->next;

	free(it);
}

void removeNodeList(TGraphL* graph, int v){
	for(int i = 0; i < graph->nn;i++){
		removeEdgeList(graph,v,i);
	}
}
