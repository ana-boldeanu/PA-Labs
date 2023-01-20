#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <set>

using namespace std;

#define N 10001

// Reprezentarea grafului
typedef struct Graph {
    int nrNodes;            // Numar de noduri
    set<int> *adjLists;     // Vector de liste de adiacente
} Graph;

// Adauga un arc orientat in graf
void add_edge(Graph *graph, int src, int dest) {
    graph->adjLists[src].insert(dest);
}

// Parcurgere DFS care gaseste toate nodurile dintr-o componenta conexa si le
// adauga in lista data ca parametru connected_nodes, recursiv. Graful este
// neorientat.
void explore_connected_component(int u, int *visited,
                              list<int> *connected_nodes, Graph *undirected) {
    visited[u] = 1;
    (*connected_nodes).push_back(u);

    for (int v : undirected->adjLists[u]) {
        if (!visited[v]) {
            explore_connected_component(v, visited,
                                        connected_nodes, undirected);
        }
    }
}

// Parcurgere DFS care determina daca exista un ciclu in graful orientat dat ca
// parametru.
bool has_cycle(Graph *graph, int src, int *in_path, int *visited) {
    if (!visited[src]) {
        // Marcheaza nodul src drept vizitat in parcurgerea DFS
        visited[src] = 1;
        // Retine faptul ca el se afla pe calea curenta
        in_path[src] = 1;

        // Viziteaza vecinii, cautand muchii de intoarcere
        for (int succ : graph->adjLists[src]) {
            if (!visited[succ] && has_cycle(graph, succ, in_path, visited)) {
                return true;

            } else if (in_path[succ]) {
                // (succ, src) este muchie de intoarcere => ciclu
                return true;
            }
        }
    }
    // La revenirea din recursivitate, elimina nodul curent din cale
    in_path[src] = 0;
    return false;
}

int main() {
    int nrNodes, nrEdges, src, dest;

    // Graful original este orientat
    Graph *directed_graph = (Graph *) calloc(1, sizeof(Graph));
    directed_graph->adjLists = new set<int>[N];

    // Versiunea neorientata a grafului original
    Graph *undirected_graph = (Graph *) calloc(1, sizeof(Graph));
    undirected_graph->adjLists = new set<int>[N];

    FILE* in = fopen("p1.in", "r");
    FILE* out = fopen("p1.out", "w");

    // Citeste datele de intrare
    fscanf(in, "%d %d\n", &nrNodes, &nrEdges);

    // Construieste cele doua grafuri folosite in algoritm
    for (int i = 0; i < nrEdges; i++) {
		fscanf(in, "%d %d\n", &src, &dest);
        add_edge(directed_graph, src, dest);
        add_edge(undirected_graph, src, dest);
        add_edge(undirected_graph, dest, src);
	}

    // Vector folosit in gasirea componentelor conexe in graful neorientat
    int visited_undirected[nrNodes + 1] = {0};

    // Vectori folositi in gasirea ciclurilor in graful original
    int visited_directed[nrNodes + 1] = {0};
    int in_path[nrNodes + 1] = {0};

    // Rezultatul final
    int min_edges = 0;

    // Parcurge toate nodurile, cautand componente conexe
    for (int u = 1; u <= nrNodes; u++) {
        if (!visited_undirected[u]) {
            // Aici se incepe explorarea unei componente conexe
            list<int> connected_nodes;  // Lista nodurilor din aceasta CC

            // DFS pentru a determina aceste noduri
            explore_connected_component(u, visited_undirected, &connected_nodes,
                                      undirected_graph);

            // In graful original, parcurge aceasta componenta conexa pentru a
            // determina daca ea contine cicluri
            bool found_cycle = false;

            for (int i : connected_nodes) {
                if (has_cycle(directed_graph, i, in_path, visited_directed)) {
                    found_cycle = true;
                    break;
                }
            }

            if (found_cycle) {
                // Daca s-a gasit un ciclu, adauga la rezultatul final atatea
                // muchii cate noduri contine componenta conexa
                min_edges += connected_nodes.size();

            } else {
                // Altfel, subgraful orientat corespunzator componentei conexe
                // poate fi sortat topologic si este nevoie doar de (numarul
                // nodurilor - 1) muchii
                min_edges += connected_nodes.size() - 1;
            }
        }
    }

    fprintf(out, "%d\n", min_edges);
    return 0;
}
