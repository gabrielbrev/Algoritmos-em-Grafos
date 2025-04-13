#include "utils/graph.h"

using namespace std;

void depthFirstSearch(Graph *g, int root_node) {
	g->assertIndex(root_node);

	int num_nodes = g->getNumNodes();

	int time = 0;
	int entry_depths[num_nodes];
	int exit_depths[num_nodes];
	int parents[num_nodes];
	vector<Edge> red_edges;
	vector<Edge> blue_edges;

	for (int i = 0; i < num_nodes; i++) {
		entry_depths[i] = 0;
		exit_depths[i] = 0;
	}

	function<void(Node * node)> _depthFirstSearch = [&](Node *node) {
		int v = node->label;

		time++;
		entry_depths[node->label] = time;

		for (int i = 0; static_cast<size_t>(i) < node->nbrs.size(); i++) {
			Node *nbr = node->nbrs[i];
			int w = nbr->label;
			Edge vw = g->getEdge(v, w);

			if (entry_depths[nbr->label] == 0) {
				blue_edges.push_back(vw);
				parents[w] = v;
				_depthFirstSearch(nbr);
			} else if (exit_depths[w] == 0 && w != parents[v]) {
				red_edges.push_back(vw);
			}
		}

		time++;
		exit_depths[node->label] = time;
	};

	_depthFirstSearch(g->getListNode(root_node));

	printf("\033[1mProfundidades de entrada e saída:\033[0m\n");
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
	printf("\n\n");

	printf("\033[1mArestas \033[34mazuis\033[0m\033[1m (árvore):\033[0m\n");
	for (const Edge &e : blue_edges) {
		printf("(%d, %d)\n", e.first, e.second);
	}
	printf("\n");

	printf("\033[1mArestas \033[31mvermelhas\033[0m\033[1m (retorno):\033[0m\n");
	for (const Edge &e : red_edges) {
		printf("(%d, %d)\n", e.first, e.second);
	}
	printf("\n");
}

int main() {
	list<Edge> edges = { make_pair(0, 1), make_pair(1, 2), make_pair(1, 3),
						 make_pair(3, 4), make_pair(3, 5), make_pair(5, 6) };
	Graph *g = new Graph(7, edges);

	g->print();
	depthFirstSearch(g, 0);

	return 0;
}