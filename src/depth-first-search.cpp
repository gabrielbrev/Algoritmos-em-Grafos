#include "utils/graph.h"
#include <set>

using namespace std;

struct ColoredEdge {
	Edge edge;
	string color;

	bool operator<(const ColoredEdge &other) const {
		return edge < other.edge; // Compara só o pair<int, int> (util para inserção em um Set)
	}
};

void depthFirstSearch(Graph *g, int root_node) {
	g->assertIndex(root_node);

	int num_nodes = g->getNumNodes();

	int time = 0;
	int entry_depths[num_nodes];
	int exit_depths[num_nodes];
	set<ColoredEdge> edges;

	for (int i = 0; i < num_nodes; i++) {
		entry_depths[i] = 0;
		exit_depths[i] = 0;
	}

	function<void(Node * node)> _depthFirstSearch = [&](Node *node) {
		time++;
		entry_depths[node->label] = time;

		for (int i = 0; static_cast<size_t>(i) < node->nbrs.size(); i++) {
			Node *nbr = node->nbrs[i];
			Edge edge = g->getEdge(node->label, nbr->label);
			if (entry_depths[nbr->label] == 0) {
				edges.insert({ edge, "blue" });
				_depthFirstSearch(nbr);
			} else {
				edges.insert({ edge, "red" });
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
	for (const ColoredEdge &ce : edges) {
		if (ce.color == "blue") {
			printf("(%d, %d)\n", ce.edge.first, ce.edge.second);
		}
	}
	printf("\n");

	printf("\033[1mArestas \033[31mvermelhas\033[0m\033[1m (retorno):\033[0m\n");
	for (const ColoredEdge &ce : edges) {
		if (ce.color == "red") {
			printf("(%d, %d)\n", ce.edge.first, ce.edge.second);
		}
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