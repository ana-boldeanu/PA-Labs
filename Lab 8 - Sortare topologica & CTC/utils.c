#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int val;          // indexul nodului (0 pt 'A' etc.)
	int d;              // momentul descoperirii pt DFS, distanta de la sursa pt BFS
    int f;              // momentul inchiderii pt DFS
	char color;
    struct Node* parent;    // parintele nodului
    struct Node* next;      // pentru folosirea nodului in lista de adiacenta 
} Node;

typedef struct {
	int nrNodes;       // numarul nodurilor din graf
	Node** adList;     // lista de adiacente (adList[0] = adresa primului nod vecin cu 'A')
} Graph;

typedef struct ListNode {       // nod din lista/stiva/coada
	int val;
	struct ListNode *next;
	struct ListNode *prev;
} ListNode;

typedef struct List {
	ListNode* head;
} List;

typedef List Stack;
typedef List Queue;

List* createList(void) {
	List* newList = (List*) calloc(1, sizeof(List));
	newList->head = (ListNode*) calloc(1, sizeof(ListNode));
	newList->head->next = newList->head->prev = newList->head;
	return newList;
}

void destroyList(List* list) {
	ListNode* it = list->head->next;

	while (it != list->head) {
		ListNode* aux = it;
		it = it->next;
		free(aux);
	}

	free(list->head);
	free(list);
}

int isListEmpty(List *list) {
	return list->head->next == list->head;
}

Stack* createStack(void) {
	return createList();
}

void destroyStack(Stack* stack) {
	destroyList(stack);
}

// Adauga noul nod la inceputul listei care reprezinta stiva
void push(Stack *stack, int val) {
	ListNode* newNode = (ListNode*) calloc(1, sizeof(ListNode));
	newNode->val = val;

	newNode->next = stack->head->next;
	newNode->prev = stack->head;

	stack->head->next->prev = newNode;
	stack->head->next = newNode;
}

// Extrage valoarea primului nod din lista (adica nodul de graf)
void pop(Stack* stack) {
	ListNode* aux = stack->head->next;
	stack->head->next = stack->head->next->next;
	stack->head->next->prev = stack->head;
	free(aux);
}

int isStackEmpty(Stack* stack) {
	return isListEmpty(stack);
}

int top(Stack* stack) {
	return stack->head->next->val;
}


Queue* createQueue(void) {
	return createList();
}

void destroyQueue(Queue* queue) {
	destroyList(queue);
}

// Adauga noul nod la inceputul listei care reprezinta coada
void enqueue(Queue *queue, int val) {
	push(queue, val);
}

// Elimina ultimul nod
void dequeue(Queue* queue) {
	ListNode* aux = queue->head->prev;
	queue->head->prev = queue->head->prev->prev;
	queue->head->prev->next = queue->head;
	free(aux);
}

int isQueueEmpty(Queue *queue) {
	return isListEmpty(queue);
}

// Intoarce valoarea ultimului nod
int front(Queue* queue) {
	return queue->head->prev->val;
}

void printQueue(Queue** queue) {
	Queue* copy = createQueue();

	printf("Q = { ");

	while(!isQueueEmpty(*queue)) {
		enqueue(copy, front(*queue));
		printf("%c ", front(*queue) + 65);
		dequeue(*queue);
	}

	printf("}\n");

    *queue = copy;
}