#include "utils/graph.h"

void depthFirstSearch(Graph *g, int root_node) {
	g->assertIndex(root_node);

	int num_nodes = g->getNumNodes();

	int time = 0;
	int entry_depths[num_nodes];
	int exit_depths[num_nodes];

	for (int i = 0; i < num_nodes; i++) {
		entry_depths[i] = 0;
		exit_depths[i] = 0;
	}

	function<void(Node node)> _depthFirstSearch = [&](Node node) {
		time++;
		entry_depths[node.label] = time;

		for (int i = 0; static_cast<size_t>(i) < node.nbrs.size(); i++) {
			Node nbr = node.nbrs[i];
			if (entry_depths[nbr.label] == 0) {
				_depthFirstSearch(nbr);
			}
		}

		time++;
		exit_depths[node.label] = time;
	};

	_depthFirstSearch(*g->getListNode(root_node));

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
}

int main() {
	list<Edge> edges = { make_pair(2, 3), make_pair(1, 2), make_pair(1, 4), make_pair(2, 4), make_pair(4, 0) };
	Graph *g = new Graph(5, edges);

	g->print();
	depthFirstSearch(g, 0);

	return 0;
}