#include <stdio.h>
#include <list>
#include <string>
#include <utility>
#include <initializer_list>
#include <functional>

using namespace std;

struct Node{
    int label;
    vector<Node> nbrs;
};

typedef pair<int, int> Edge;

class Graph {
    private:
        int num_nodes;
        int** adj_matrix;
        Node* adj_list;

    public:
        Graph(int num_nodes, list<Edge> edges) {
            this->num_nodes = num_nodes;
            this->adj_matrix = new int*[num_nodes];
            this->adj_list = new Node[num_nodes];

            for (int i = 0; i < num_nodes; i++) {
                // Inicializando a matriz
                this->adj_matrix[i] = new int[num_nodes];
                for (int j = 0; j < num_nodes; j++) {
                    this->adj_matrix[i][j] = 0;
                }

                // Inicializando a lista
                Node node = { i, vector<Node>() };
                this->adj_list[i] = node;
            }

            for (Edge e : edges) {
                int a = e.first;
                int b = e.second;

                // Preenchendo a matriz
                this->adj_matrix[a][b] = 1;
                this->adj_matrix[b][a] = 1;

                // Preenchendo a lista
                this->adj_list[a].nbrs.push_back(this->adj_list[b]);
                this->adj_list[b].nbrs.push_back(this->adj_list[a]);
            }
        }

        int getNumNodes() {
            return this->num_nodes;
        }
        
        void assertIndex(int i) {
            if (i < 0) {
                throw invalid_argument("received negative value");
            }

            if (i > this->num_nodes) {
                throw invalid_argument("node does not exist");
            }
        }

        void createEdge(int a, int b) {
            if (a == b) throw logic_error("can't create loops");

            assertIndex(a);
            assertIndex(b);

            Edge edge = make_pair(a, b);

            // Checando se já existe
            for (Node node : this->adj_list[a].nbrs) if (node.label == b) return;
            
            // Adicionando na lista
            this->adj_list[a].nbrs.push_back(this->adj_list[b]);
            this->adj_list[b].nbrs.push_back(this->adj_list[a]);

            // Adidionando na matriz
            this->adj_matrix[a][b] = 1;
            this->adj_matrix[b][a] = 1;
        }

        void depthFirstSearch(int root_node, function<void(Node node)> func = NULL) {
            assertIndex(root_node);            

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
    
                for (int i = 0; i < node.nbrs.size(); i++) {
                    Node nbr = node.nbrs[i];
                    if (entry_depths[nbr.label] == 0) {
                        _depthFirstSearch(nbr);
                    }
                }
    
                time++;
                exit_depths[node.label] = time;
            };

            _depthFirstSearch(this->adj_list[root_node]);

            printf("\033[1mProfundidades de entrada e saída:\033[0m\n");
            for (int i = 0; i < this->num_nodes; i++) {
                printf("\033[38;5;226m%d\t\033[0m", i);
            }
            printf("\n");
            for (int i = 0; i < this->num_nodes; i++) {
                printf("%d\t", entry_depths[i]);
            }
            printf("\n");
            for (int i = 0; i < this->num_nodes; i++) {
                printf("%d\t", exit_depths[i]);
            }
            printf("\n\n");
        }
        
        void print() {
            // Printando a matriz
            printf("\033[1mMatriz de ajacências:\033[0m\n   ");
            for (int i = 0; i < num_nodes; i++) {
                printf("\033[38;5;226m%d  \033[0m", i);
            }
            printf("\n");
            for (int i = 0; i < num_nodes; i++) {
                printf("\033[38;5;226m%d  \033[0m", i);
                for (int j = 0; j < num_nodes; j++) {
                    if (this->adj_matrix[i][j] == 1 && j > i) {
                        printf("\033[97m%d  \033[0m", this->adj_matrix[i][j]);
                    } else {
                        printf("\033[30m%d  \033[0m", this->adj_matrix[i][j]);
                    }
                }
                printf("\n");
            }
            printf("\n");

            // Printando a lista
            printf("\033[1mLista de ajacências:\033[0m\n");
            for (int i = 0; i < num_nodes; i++) {
                    Node node = this->adj_list[i];
                    printf("\033[38;5;226m%d:\033[0m { ", node.label);
                    int count = 0;
                    for (Node nbr : node.nbrs) {
                        printf("%d", nbr.label);
                        count++;
                        if (count != node.nbrs.size()) {
                            printf(", ");
                        }
                    }
                    printf(" }\n");
                }
                printf("\n");

        }
};

int main() {
    list<Edge> edges = { make_pair(2, 3), make_pair(1, 2), make_pair(1, 4), make_pair(2, 4), make_pair(4, 0) };
    Graph* g = new Graph(5, edges);

    g->print();
    g->depthFirstSearch(0);

    return 0;
}