#include "graph.h"
#include "heap.h"
#include <limits>
#include <sstream>

using namespace std;

// Constructor
Graph::Graph(){}

// Method initializes all the nodes in the graph in order to run
// Dijkstra's shortest path algorithm
void Graph::InitializeSingleSource(GRAPH* graph, int source) {

   for(int i = 1; i <= graph->v; i++) {
        
        graph->H[i].d = std::numeric_limits<int>::max(); // Setting node distance 
                                                         //to max possible value
        graph->H[i].p = 0; // Each node's predecessor is nil
   }

   graph->H[source].d = 0; // The source node's distance

}


// Method determines if there is a new shortest distance from source node u to v
void Graph::Relax(ELEMENT* u, ELEMENT* v, LIST* w) {
    
    if(v->d > (u->d + w->weight)) {
        v->d = u->d + w->weight; // Update distance
        v->p = u->node; // Update predecessor 
    }
}


// Method performs Dijkstra's shortest path algorithm and returns either a
// length or path as a string
string Graph::DijkstraSP(GRAPH* graph, int source, int dest, int flag) {
   
    // Checking to see whether flag is valid
    bool invalid = false;
    if(flag != 0 && flag != 1) {
        invalid = true;
    }
    
    string sp = ""; // String to return
    // If invalid node and flag value
    if((dest > graph->v || source > graph->v) && invalid) { 
        cout << "Error: One or more of the nodes is invalid." << endl;
        sp = "Error: Invalid flag value";
        return sp;
    }
    else if(dest > graph->v || source > graph->v) {// If invalid node
        sp = "Error: One or more of the nodes is invalid.";
        return sp;
    }
    else if(invalid) {// If invalide flag value
        sp = "Error: Invalid flag value";
        return sp;
    }

    // Perform Dijkstra's shortest path algorithm
    InitializeSingleSource(graph, source); // Initialize each node
    Heap heap;
    ELEMENT S[graph->v + 1]; // To hold extracted nodes
    int nodes = graph->v; // To hold initial # of vertices
    stringstream ss; // To help with converting int to string

    while(graph->v != 0) {
        ELEMENT u = heap.DeleteMin(graph); // Extracted node
        S[u.node] = u; // Adding extracted node to index corresponding to node value
        LIST* temp = graph->A[u.node];

        // Checking adjaceny list
        while(temp != NULL) {

            int adj = temp->neighbor;
            for(int i = 1; i <= graph->v; i++) {
             
                if(graph->H[i].node == adj) { // If node hasn't been extracted
                    Relax(&u, &graph->H[i], temp);
                }
            }
            temp = temp->next;
         }
    }

    // Returning string based on command given
    if(S[dest].d < 0 || S[dest].d > // If distance to node is infinity
            std::numeric_limits<int>::max()/1.5) {
        ss << "Sorry, node " << dest << " is not reachable " 
        << "from node " << source << ".";
        sp = ss.str(); // String to return

    }   
    else if(flag == 0) { // If node and path exist and flag is 0
        ss << S[dest].d; // Adding destination distance to ss
        sp = "LENGTH: " + ss.str(); // String to return
    }
    else { // If node and path exist and flag value is 1
                
        // Storing the path from s-t in string sp
        stringstream stream; // Creating new stream object
        stream << S[source].node; 
        sp += stream.str(); // Adding source to path
        sp += findPath(S, source, dest, nodes);

        // Adding commas to string
        ss << sp[0];
        for(int i = 1; i < sp.size(); i++)
            ss << ", " << sp[i];

            sp = "PATH: " + ss.str(); // String to return
        }
      
    // Resetting pointers that were modified
    graph->v = nodes;
    for(int i = 1; i <= graph->v; i++) {
        graph->H[i].node = i;
        graph->H[i].d = 0;
        graph->H[i].p = 0;
    }

    return sp;
}


// Helper method to find the path from a source to a destination
string Graph::findPath(ELEMENT S[], int source, int dest, int v_G) {

    std::string path = ""; // String to return

    // Recursively add path nodes to string 
    if(S[dest].node != S[source].node) { 
        path += findPath(S, source, S[dest].p, v_G); // Look for next node in path
        stringstream ss;
        ss << S[dest].node; // ss is equal to path node
        path += ss.str(); // Adding path node to return string
    }

    return path;
}



