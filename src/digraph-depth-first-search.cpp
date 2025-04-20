#include "utils/digraph.h"
#include <vector>

void depthFirstSearch(Digraph *dg, int root_node) {
	int time = 0;
	int num_nodes = dg->getNumNodes();
	int entry_depths[num_nodes];
	int exit_depths[num_nodes];
	int parents[num_nodes];

	vector<Edge> blue_edges;
	vector<Edge> red_edges;
	vector<Edge> yellow_edges;
	vector<Edge> green_edges;

	for (int i = 0; i < num_nodes; i++) {
		entry_depths[i] = 0;
		exit_depths[i] = 0;
		parents[i] = -1;
	}

	function<void(Node * node)> _depthFirstSearch = [&](Node *node) {
		int v = node->label;
		entry_depths[v] = ++time;

		for (Node *nbr : node->nbrs) {
			int w = nbr->label;
			Edge vw = dg->getEdge(v, w);

			if (entry_depths[w] == 0) {
				blue_edges.push_back(vw);
				parents[w] = v;
				_depthFirstSearch(nbr);
			} else {
				if (exit_depths[w] == 0) {
					red_edges.push_back(vw);
				} else if (entry_depths[v] < entry_depths[w]) {
					yellow_edges.push_back(vw);
				} else {
					green_edges.push_back(vw);
				}
			}
		}

		exit_depths[v] = ++time;
	};

	_depthFirstSearch(dg->getListNode(root_node));

	for (int i = 0; i < num_nodes; i++) {
		if (entry_depths[i] == 0) {
			_depthFirstSearch(dg->getListNode(i));
		}
	}

	// Imprimir os resultados da busca em profundidade
	printf("\033[1mProfundidade de entrada e saída, pai e back:\033[0m\n");
	for (int i = 0; i < num_nodes; i++) {
		printf("\033[38;5;226m%d\t\033[0m", i);
	}
	printf("\n");
	for (int i = 0; i < num_nodes; i++) {
		printf("%d\t", entry_depths[i]);
	}
	printf("\n");
	for (int i = 0; i < num_nodes; i++) {
		printf("%d\t", exit_depths[i]);
	}
	printf("\n");
	for (int i = 0; i < num_nodes; i++) {
		printf("%d\t", parents[i]);
	}
	printf("\n\n");

	if (blue_edges.empty()) {
		printf("\033[1mNenhuma aresta \033[34mazul\033[0m\033[1m (árvore) encontrada.\033[0m\n\n");
	} else {
		printf("\033[1mArestas \033[34mazuis\033[0m \033[1m(árvore):\033[0m\n");
		for (const Edge &e : blue_edges) {
			printf("(%d, %d)\n", e.first, e.second);
		}
		printf("\n");
	}

	if (red_edges.empty()) {
		printf("\033[1mNenhuma aresta \033[31mvermelha\033[0m\033[1m (retorno) encontrada.\033[0m\n\n");
	} else {
		printf("\033[1mArestas \033[31mvermelhas\033[0m \033[1m(retorno):\033[0m\n");
		for (const Edge &e : red_edges) {
			printf("(%d, %d)\n", e.first, e.second);
		}
		printf("\n");
	}

	if (yellow_edges.empty()) {
		printf("\033[1mNenhuma aresta \033[33mamarela\033[0m \033[1m(cruzamento) encontrada.\033[0m\n\n");
	} else {
		printf("\033[1mArestas \033[33mamarelas\033[0m \033[1m(cruzamento):\033[0m\n");
		for (const Edge &e : yellow_edges) {
			printf("(%d, %d)\n", e.first, e.second);
		}
		printf("\n");
	}

	if (green_edges.empty()) {
		printf("\033[1mNenhuma aresta \033[32mverde\033[0m \033[1m(avanço) encontrada.\033[0m\n\n");
	} else {
		printf("\033[1mArestas \033[32mverdes\033[0m \033[1m(avanço):\033[0m\n");
		for (const Edge &e : green_edges) {
			printf("(%d, %d)\n", e.first, e.second);
		}
		printf("\n");
	}
}

int main() {
	list<Edge> edges = { { 0, 1 }, { 0, 2 }, { 0, 3 }, { 1, 2 }, { 2, 0 }, { 2, 3 }, { 4, 1 }, { 4, 5 },
						 { 4, 6 }, { 5, 6 }, { 6, 4 }, { 7, 5 }, { 8, 9 }, { 9, 8 }, { 9, 7 }, { 9, 6 } };
	Digraph *dg = new Digraph(10, edges);
	dg->print();

	depthFirstSearch(dg, 0);

	return 0;
}
