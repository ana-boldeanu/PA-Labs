#include <stdio.h>
#include <stdlib.h>
#include "utils.c"

// Aloca spatiu pentru graf
Graph* createGraphAdjList(int nrNodes) {
	Graph* graph = calloc(1, sizeof(Graph));

	graph->nrNodes = nrNodes;
	graph->adList = calloc(nrNodes, sizeof(Node*));

	return graph;
}

// Adauga arcul u -> v (adauga v la sfarsitul listei de adiacenta a lui v)
void addEdgeList(Graph* graph, int u, int v) {
	Node *node = calloc(1, sizeof(Node));
	node->val = v;
	node->next = NULL;

    Node *it = graph->adList[u];

    if (it != NULL) {
        while (it->next != NULL) {
            it = it->next;
        }
        it->next = node;

    } else {
        graph->adList[u] = node;
    }	
}

void destroyGraphAdjList(Graph* graph){
	for (int i = 0; i < graph->nrNodes; i++) {
		
		Node *p = graph->adList[i];
		Node *temp = p;
		
		while(p != NULL)
		{
			temp = p;
			p = p->next;
			free(temp);
		}
	}

	free(graph->adList);
	free(graph);

}

void removeEdgeList(Graph* graph, int v1, int v2){
	Node* it = graph->adList[v1];
	Node* prev = NULL;
	while(it != NULL && it->val != v2){
		prev = it;
		it = it->next;
	}

	if(it == NULL)return;

	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adList[v1] = it->next;
	free(it);

	it = graph->adList[v2];
	prev = NULL;
	while (it != NULL && it->val != v1){
		prev = it;
		it = it->next;
	}
	if (it == NULL) return;
	if (prev != NULL)
		prev->next = it->next;
	else
		graph->adList[v2] = it->next;

	free(it);
}

void removeNodeList(Graph* graph, int v){
	for(int i = 0; i < graph->nrNodes;i++){
		removeEdgeList(graph,v,i);
	}
}

