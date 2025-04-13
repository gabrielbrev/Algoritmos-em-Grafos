#ifndef GRAPH_H
#define GRAPH_H

#include <functional>
#include <list>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct Node {
	int label;
	vector<Node> nbrs;
};

typedef pair<int, int> Edge;

class Graph {
	private:
	int num_nodes;
	int **adj_matrix;
	Node *adj_list;

	public:
	Graph(int num_nodes, list<Edge> edges);

	int getNumNodes();
	Node *getListNode(int num);
	Edge getEdge(int a, int b);

	void assertIndex(int i);
	void createEdge(int a, int b);
	void print();
};

#endif