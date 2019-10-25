#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <string>

struct ELEMENT {
    int node;
    int d;
    int p; 
};

struct LIST {
    int neighbor;
    int weight;
    struct LIST* next;
};

struct GRAPH {
    int v;
    int e;
    struct ELEMENT* H;
    struct LIST** A;
};

class Graph {

private:
    
    // Helper method
    std::string findPath(ELEMENT S[], int source, int dest, int v_G);

public:

    // Module functions
    Graph();
    void InitializeSingleSource(GRAPH* graph, int source);
    void Relax(ELEMENT* u, ELEMENT* v, LIST* w);
    std::string DijkstraSP(GRAPH* graph, int source, int dest, int flag);

};

#endif
