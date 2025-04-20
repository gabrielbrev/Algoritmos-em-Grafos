#include "digraph.h"

Digraph::Digraph(int num_nodes, list<Edge> edges) {
	this->num_nodes = num_nodes;
	this->adj_matrix = new int *[num_nodes];
	this->adj_list = new Node[num_nodes];

	for (int i = 0; i < num_nodes; i++) {
		this->adj_matrix[i] = new int[num_nodes];
		for (int j = 0; j < num_nodes; j++) {
			this->adj_matrix[i][j] = 0;
		}

		Node node = { i, vector<Node *>() };
		this->adj_list[i] = node;
	}

	for (Edge e : edges) {
		int a = e.first;
		int b = e.second;

		this->adj_matrix[a][b] = 1;

		this->adj_list[a].nbrs.push_back(&this->adj_list[b]);
	}
}

int Digraph::getNumNodes() {
	return this->num_nodes;
}

Node *Digraph::getListNode(int num) {
	this->assertIndex(num);
	return &this->adj_list[num];
}

Edge Digraph::getEdge(int a, int b) {
	assertIndex(a);
	assertIndex(b);

	if (a == b || this->adj_matrix[a][b] == 0) {
		throw logic_error("edge does not exist");
	}

	return make_pair(a, b);
}

void Digraph::assertIndex(int i) {
	if (i < 0) {
		throw invalid_argument("received negative value");
	}

	if (i >= this->num_nodes) {
		throw invalid_argument("node does not exist");
	}
}

void Digraph::createEdge(int a, int b) {
	if (a == b)
		throw logic_error("can't create loops");

	assertIndex(a);
	assertIndex(b);

	if (this->adj_matrix[a][b] == 1) {
		return;
	}

	this->adj_list[a].nbrs.push_back(&this->adj_list[b]);

	this->adj_matrix[a][b] = 1;
}

void Digraph::print() {
	printf("\033[1mMatriz de adjacências:\033[0m\n   ");
	for (int i = 0; i < num_nodes; i++) {
		printf("\033[38;5;226m%d  \033[0m", i);
	}
	printf("\n");
	for (int i = 0; i < num_nodes; i++) {
		printf("\033[38;5;226m%d  \033[0m", i);
		for (int j = 0; j < num_nodes; j++) {
			if (this->adj_matrix[i][j] == 1) {
				printf("\033[97m%d  \033[0m", this->adj_matrix[i][j]);
			} else {
				printf("\033[30m%d  \033[0m", this->adj_matrix[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");

	printf("\033[1mLista de adjacências:\033[0m\n");
	for (int i = 0; i < num_nodes; i++) {
		Node node = this->adj_list[i];
		printf("\033[38;5;226m%d:\033[0m { ", node.label);
		int count = 0;
		for (Node *nbr : node.nbrs) {
			printf("%d", nbr->label);
			count++;
			if (static_cast<size_t>(count) != node.nbrs.size()) {
				printf(", ");
			}
		}
		printf(" }\n");
	}
	printf("\n");
}