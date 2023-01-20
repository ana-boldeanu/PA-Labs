#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Util.h"
#include "Graph.h"

int timp;
int d[400];
int f[400];

TGraphL* createGraphAdjList(int numberOfNodes) {
	//TODO: 1
	TGraphL* graph = malloc(sizeof(TGraphL));
	graph->nn = numberOfNodes;

	graph->adl = malloc(numberOfNodes * sizeof(ATNode));

	int i;
	for (i = 0; i < numberOfNodes; i++) {
		graph->adl[i] = NULL;
	}
	return graph;
}

void addEdgeList(TGraphL* graph, TGraphL* transpose, int v1, int v2) {
	//TODO: 1
	ATNode node1 = malloc(sizeof(TNode));
	node1->v = v2;
	node1->next = NULL;

	node1->next = graph->adl[v1];
	graph->adl[v1] = node1;

	ATNode node1_trans = malloc(sizeof(TNode));
	node1_trans->v = v1;
	node1_trans->next = NULL;

	node1_trans->next = transpose->adl[v2];
	transpose->adl[v2] = node1_trans;
}

int timp2 = 0;
void dfsUtil(TGraphL* graph, int* visited, int* parent,  int s) {
	//TODO: 3
	ATNode temp = graph->adl[s];
	timp2 = timp2 + 1;
	visited[s] = 1;
	d[s] = timp2;
	printf("nod:%c  culoare:%d  d:%d   \n", s + 65, visited[s], d[s]);

	while(temp != NULL)
	{
		if(visited[temp->v] == 0) {
			parent[temp->v] = s;
			dfsUtil(graph, visited, parent, temp->v);
		}
		temp = temp->next;
	}
	timp2 = timp2 + 1;
	f[s] = timp2;
	visited[s] = 2;
}

int dist[30];
void explore(TGraphL* graph, int* visited, int* parent, List* path, int s) {
	//TODO: 3
	ATNode temp = graph->adl[s];
	timp = timp + 1;
	visited[s] = 1;
	dist[s] = timp;

	while(temp != NULL)
	{
		if(visited[temp->v] == 0) {
			parent[temp->v] = s;
			explore(graph, visited, parent, path, temp->v);
		}
		temp = temp->next;
	}
	timp = timp + 1;
	f[s] = timp;
	visited[s] = 2;
	push(path, s);
}

int distance[30];
int final[30];
int timpSSc;
void SSCexplore(TGraphL* graph, int* visited, int* parent, List* path, int s) {
	//TODO: 3
	ATNode temp = graph->adl[s];
	timpSSc = timpSSc + 1;
	visited[s] = 1;
	distance[s] = timpSSc;

	while(temp != NULL)
	{
		if(visited[temp->v] == 0) {
			parent[temp->v] = s;
			explore(graph, visited, parent, path, temp->v);
		}
		temp = temp->next;
	}
	timpSSc = timpSSc + 1;
	final[s] = timpSSc;
	visited[s] = 2;
	push(path, s);
}

void topologicalSort(TGraphL* graph) {
	int visited[10] = {0};
	int parents[10] = {0};
	Stack* stack = createStack();

	for (int i = graph->nn - 1; i >= 0; i--) {
		if (visited[i] == 0) {
			explore(graph, visited, parents, stack, i);
		}
	}

	while(!isStackEmpty(stack)) {
		printf("%c\n", top(stack) + 65);
		pop(stack);
	}
}

void strongly_connected_components(TGraphL* graph, TGraphL* transpose) {
	Stack* stack = createStack();
	int visited[30] = {0};
	int parents[30] = {0};

	for (int i = 0; i < graph->nn; i++) {
		if (visited[i] == 0) {
			SSCexplore(graph, visited, parents, stack, i);
		}
	}

	int visited2[30] = {0};
	while(!isStackEmpty(stack)) {
		int v = top(stack);
		pop(stack);
		if(visited2[v] == 0) {
			printf("componenta: \n");
			dfsUtil(transpose, visited2, parents, v);
			printf("\n");
		}
	}
}


int main(int argc, char **argv) {

   printf("Sortare topologica:\n");
   TGraphL* G1 =  createGraphAdjList(7);
   TGraphL* G1_transpose =  createGraphAdjList(7);
   addEdgeList(G1, G1_transpose, 0, 1); 
   addEdgeList(G1, G1_transpose, 0, 3); 
   addEdgeList(G1, G1_transpose, 0, 6); 
   addEdgeList(G1, G1_transpose, 1, 6); 
   addEdgeList(G1, G1_transpose, 3, 4); 
   addEdgeList(G1, G1_transpose, 5, 4); 
   addEdgeList(G1, G1_transpose, 6, 2); 
   topologicalSort(G1);


   printf("Componente conexe: \n");
   TGraphL* G2 =  createGraphAdjList(16);
   TGraphL* G2_transpose =  createGraphAdjList(16);
   addEdgeList(G2, G2_transpose, 0, 1); 
   addEdgeList(G2, G2_transpose, 1, 6); 
   addEdgeList(G2, G2_transpose, 0, 6); 
   addEdgeList(G2, G2_transpose, 6, 7); 
   addEdgeList(G2, G2_transpose, 1, 2); 
   addEdgeList(G2, G2_transpose, 2, 4); 
   addEdgeList(G2, G2_transpose, 4, 3);
   addEdgeList(G2, G2_transpose, 3, 2);
   addEdgeList(G2, G2_transpose, 3, 5);
   addEdgeList(G2, G2_transpose, 8, 0); 
   addEdgeList(G2, G2_transpose, 8, 9);
   addEdgeList(G2, G2_transpose, 9, 10);
   addEdgeList(G2, G2_transpose, 8, 11);
   addEdgeList(G2, G2_transpose, 10, 8);
   addEdgeList(G2, G2_transpose, 11, 10);
   addEdgeList(G2, G2_transpose, 10, 12);
   addEdgeList(G2, G2_transpose, 12, 13);
   addEdgeList(G2, G2_transpose, 13, 14);
   addEdgeList(G2, G2_transpose, 14, 12);
   addEdgeList(G2, G2_transpose, 14, 15);

   strongly_connected_components(G2, G2_transpose);


        
	return 0;
}