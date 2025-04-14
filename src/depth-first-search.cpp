#include "utils/graph.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <format>
#include <sstream>

using namespace std;

void depthFirstSearch(Graph *g, int root_node) {
	g->assertIndex(root_node);

	int num_nodes = g->getNumNodes();

	int time = 0;
	int entry_depths[num_nodes];
	int exit_depths[num_nodes];
	int parents[num_nodes];
	int back_values[num_nodes];

	vector<Edge> red_edges;
	vector<Edge> blue_edges;
	vector<Edge> edge_stack;
	vector<Edge> bridges;
	vector<vector<Edge>> blocks;

	for (int i = 0; i < num_nodes; i++) {
		entry_depths[i] = 0;
		exit_depths[i] = 0;
		parents[i] = -1;
		back_values[i] = 0;
	}

	function<void(Node * node)> _depthFirstSearch = [&](Node *node) {
		int v = node->label;

		time++;
		entry_depths[v] = back_values[v] = time;

		for (int i = 0; static_cast<size_t>(i) < node->nbrs.size(); i++) {
			Node *nbr = node->nbrs[i];
			int w = nbr->label;
			Edge vw = g->getEdge(v, w);

			if (entry_depths[w] == 0) {
				blue_edges.push_back(vw);
				edge_stack.push_back(vw);
				parents[w] = v;
				_depthFirstSearch(nbr);

				if (back_values[w] >= entry_depths[v]) {
					vector<Edge> block;

					while (edge_stack.size() > 0) {
						Edge e = edge_stack.back();

						block.push_back(e);
						edge_stack.pop_back();

						if (e == vw) {
							break;
						}
					}

					if (block.size() > 0) {
						blocks.push_back(block);

						if (block.size() == 1) {
							bridges.push_back(block.front());
						}
					}
				}

				back_values[v] = min(back_values[v], back_values[w]);
			} else if (exit_depths[w] == 0 && w != parents[v]) {
				red_edges.push_back(vw);
				edge_stack.push_back(vw);
				back_values[v] = min(back_values[v], entry_depths[w]);
			}
		}

		time++;
		exit_depths[v] = time;
	};

	_depthFirstSearch(g->getListNode(root_node));

	vector<int> cut_vertices;
	for (int v = 0; v < num_nodes; v++) {
		if (v == root_node) {
			int children = 0;
			for (int w = 0; w < num_nodes; w++) {
				if (parents[w] == v) {
					children++;
				}

				if (children == 2) {
					cut_vertices.push_back(v);
					break;
				}
			}
		} else {
			for (int w = 0; w < num_nodes; w++) {
				if (parents[w] == v && back_values[w] >= entry_depths[v]) {
					cut_vertices.push_back(v);
					break;
				}
			}
		}
	}

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
	printf("\n");
	for (int i = 0; i < num_nodes; i++) {
		printf("%d\t", back_values[i]);
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

	if (!cut_vertices.empty()) {
		printf("\033[1mArticulações:\033[0m ");
		for (size_t i = 0; i < cut_vertices.size(); ++i) {
			printf("%d", cut_vertices[i]);
			if (i != cut_vertices.size() - 1) {
				printf(", ");
			}
		}
		printf("\n\n");
	} else {
		printf("\033[1mNenhuma articulação encontrada.\033[0m\n\n");
	}

	if (!bridges.empty()) {
		printf("\033[1mPontes:\033[0m\n");
		for (const Edge &e : bridges) {
			printf("(%d, %d)\n", e.first, e.second);
		}
		printf("\n");
	} else {
		printf("\033[1mNenhuma ponte encontrada.\033[0m\n\n");
	}

	for (size_t i = 0; i < blocks.size(); i++) {
		printf("\033[1mBloco %zu:\033[0m\n", i + 1);
		for (const Edge &e : blocks[i]) {
			printf("(%d, %d)\n", e.first, e.second);
		}
		printf("\n");
	}
}

int main() {
	list<Edge> edges = { make_pair(0, 1), make_pair(0, 2), make_pair(0, 3), make_pair(1, 2), make_pair(3, 2),
						 make_pair(3, 4), make_pair(4, 5), make_pair(4, 6), make_pair(5, 6) };
	Graph *g = new Graph(7, edges);

	g->print();
	depthFirstSearch(g, 0);

	return 0;
}