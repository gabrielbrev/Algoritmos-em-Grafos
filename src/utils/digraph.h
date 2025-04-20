#ifndef DIGRAPH_H
#define DIGRAPH_H

#include "graph.h"
#include <vector>

class Digraph {
	private:
	int num_nodes;
	int **adj_matrix;
	Node *adj_list;

	public:
	Digraph(int num_nodes, list<Edge> edges);

	int getNumNodes();
	Node *getListNode(int num);
	Edge getEdge(int a, int b);

	void assertIndex(int i);
	void createEdge(int a, int b);
	void print();
};

#endif