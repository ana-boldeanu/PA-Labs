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

	int i;
	for (i = 0; i < numberOfNodes; i++) {
		graph->adl[i] = NULL;
	}
	return graph;
}

void addEdgeList(TGraphL* graph, int v1, int v2) {
	//TODO: 1
	ATNode node1 = malloc(sizeof(TNode));
	node1->v = v2;
	node1->next = NULL;

	node1->next = graph->adl[v1];
	graph->adl[v1] = node1;
}


int c[100];
int p[100];

int timp;
int d[400];
int f[400];

void dfsRecHelper(TGraphL* graph, int* visited, int* parent, List* path, int s) {
	//TODO: 3
	ATNode temp = graph->adl[s];
	timp = timp + 1;
	visited[s] = 1;
	d[s] = timp;
	enqueue(path, s);
	printf("nod:%c  culoare:%d  d:%d  parinte:%c  \n", s + 65, visited[s], d[s],  parent[s] + 65);

	while(temp != NULL)
	{
		if(visited[temp->v] == 0) {
			parent[temp->v] = s;
			dfsRecHelper(graph, visited, parent, path, temp->v);
		}
		temp = temp->next;
	}
	timp = timp + 1;
	f[s] = timp;
	visited[s] = 2;
	printf("nod:%c  culoare:%d  f:%d  parinte:%c  \n", s + 65, visited[s], f[s], parent[s] + 65);
}


List* dfsRecursive(TGraphL* graph, int s) {
	// TODO 3
	int *visited = calloc(40, sizeof(int));
	int *parent = calloc(40, sizeof(int));
	Queue* q = createQueue();

	for(int i = 0; i < graph->nn; i++){
		parent[i] = 0;
		visited[i] = 0;
	}

	for(int i = 0; i < graph->nn; i++){
		if(visited[i] == 0)
			dfsRecHelper( graph, visited, parent, q, i);
	}
	

	free(visited);
	return q;
}


List* bfs(TGraphL* graph, int s){
	// TODO: 4
	Queue* q = createQueue();
	Queue* list = createQueue();
	int visited[30] = {0};
	int parent[30] = {0};
	int dist[30] = {10000};
	
	visited[s] = 1;
	dist[s] = 0;
	printf("nod:%c  culoare:%d  dist:%d  \n", s + 65, visited[s], dist[s]);

	enqueue(q, s);

	while(!isQueueEmpty(q))
	{
		int nod = front(q);
		dequeue(q);
		enqueue(list, nod);

		ATNode temp = graph->adl[nod];
		while(temp)
		{
			if(visited[temp->v] == 0)
			{
				dist[temp->v] = dist[nod] + 1;
				visited[temp->v] = 1;
				parent[temp->v] = nod;
				printf("nod:%c  culoare:%d  dist:%d  parinte:%c  \n", temp->v + 65, visited[temp->v], dist[temp->v], parent[temp->v] + 65);
				enqueue(q, temp->v);
			}
			temp = temp->next;
		}
		visited[nod] = 2;
		printf("nod:%c  culoare:%d \n", nod + 65, visited[nod]);
	}
	destroyQueue(q);
	return list;
}

void destroyGraphAdjList(TGraphL* graph){
	// TODO: 5

	for (int i = 0; i < graph->nn; i++) {
		
		ATNode p = graph->adl[i];
		ATNode temp = p;
		
		while(p != NULL)
		{
			temp = p;
			p = p->next;
			free(temp);
		}
	}

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

void explore(TGraphL* graph, int* visited, int* parent, List* path, int s) {
	//TODO: 3
	ATNode temp = graph->adl[s];
	timp = timp + 1;
	visited[s] = 1;
	d[s] = timp;
	//enqueue(path, s);
	//printf("nod:%c  culoare:%d   parinte:%c  \n", s + 65, visited[s],  parent[s] + 65);

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
	//printf("nod:%c  culoare:%d   parinte:%c  \n", s + 65, visited[s], parent[s] + 65);
}

void topSort(TGraphL* graph) {
	int visited[10] = {0};
	int parents[10] = {0};
	Stack* stack = createStack();

	for (int i = 0; i < graph->nn; i++) {
		if (visited[i] == 0) {
			explore(graph, visited, parents, stack, i);
		}
	}

	printf("Sortare topologica \n");
	while(!isStackEmpty(stack)) {
		printf("%c ", top(stack)+65);
		pop(stack);
	}
}

int main(int argc, char **argv) {

   TGraphL* G =  createGraphAdjList(10);
   addEdgeList(G, 0, 7);
   addEdgeList(G, 0, 2);
   addEdgeList(G, 0, 1);
   addEdgeList(G, 1, 8);
   addEdgeList(G, 1, 7);
   addEdgeList(G, 1, 4);
   addEdgeList(G, 1, 3);
   addEdgeList(G, 2, 3);
   addEdgeList(G, 3, 9);
   addEdgeList(G, 3, 4);
   addEdgeList(G, 4, 6);
   addEdgeList(G, 4, 5);
   addEdgeList(G, 5, 6);
   addEdgeList(G, 7, 8);
   addEdgeList(G, 8, 0);
   dfsRecursive(G, 0);
   printf("\n");
   printf("\n");
   bfs(G, 0);


printf("\n");
   printf("\n");
   TGraphL* G2 =  createGraphAdjList(7);
   addEdgeList(G2, 0, 1); // A B
   addEdgeList(G2, 0, 3); // A D
   addEdgeList(G2, 0, 6); // A G
   addEdgeList(G2, 1, 6); // B G
   addEdgeList(G2, 3, 4); // D E
   addEdgeList(G2, 5, 4); // F E
   addEdgeList(G2, 6, 2); // G C

   topSort(G2);
        
	return 0;
}