#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "heap.h"
#include "util.h"
#include "graph.h"

/**
 * Name: Edgar Chaidez
 * Class: CSE 310
 * Description: Main program that takes in commands that read in a graph
 * of vertices, prints out the graphs adjacency list, and performs 
 * Dijkstra's shortest path algorithm.
 */

// Executes certain heap functions depending on what command is given.
int main()
{
    Graph g; // Creating a Graph class object
    Heap heap; 
    Util comm; // Creating a Util class object
    struct GRAPH* graph = new GRAPH; // Creating a GRAPH data type pointer

    ifstream inputFile; // For reading in file
    
    bool fileRead = false; // Determines if file has been read

    // variables for the parser
    char c;
    int s, t, iFlag;
    string sp; // For command C
    
    // Loop infinitely until command to exit is given
    while(1){   

        c = comm.nextCommand(&s, &t, &iFlag);
        switch (c) {

            // Exit command
            case 'e':
            case 'E': 
                printf("COMMAND: %c.\n", c); 

                exit(0); // Exit from loop


            // Performs Dijkstra's shortest path algorithm
            case 'c':
            case 'C':
                printf("COMMAND: %c %d %d %d. \n", c, s, t, iFlag);
              
                if(fileRead) {                
                    sp = g.DijkstraSP(graph, s, t, iFlag);
                
                    cout << sp << endl;
                }
                else
                    cout << "Error: There is no graph to run Dijkstra's" <<
                        " algorithm on." << endl;
                
                break;


            // Prints graph
            case 'w':
            case 'W':
                printf("COMMAND: %c. \n", c);

                if(fileRead)
                    heap.printHeap(graph);
                else
                    cout << "Error: There is no graph to print." << endl;
              
                break;


            // Reads in graph from file
            case 'i':
            case 'I':
                printf("COMMAND: %c. \n", c);
                
                inputFile.open("Ginput.txt"); // Opening file


                if(inputFile.is_open()) { 
                  
                    // If file has been read before, delete old allocated
                    // memory 
                    if(fileRead) {
                        // Deleting H array
                        delete[] graph->H;
                        graph->H = NULL;
                        
                        // Deleting linked list at each A index
                        for(int i = 1; i <= graph->v; i++) {
                            struct LIST* head = graph->A[i];
                            struct LIST* temp = head;

                            while(temp != NULL) {
                                temp = temp->next;
                                delete head;
                                head = NULL;
                                head = temp;
                            }
                        }
                        
                        // Deleting A array
                        delete[] graph->A;
                        graph->A = NULL;
                    } 

                    fileRead = true;
                    int vertices, edges;
                    inputFile >> vertices; // Reading in num of vertices
                    inputFile >> edges; // Reading in num of edges

                    graph->v = vertices;
                    graph->e = edges;

                    // Allocating memory for A and H arrays
                    graph->A = new LIST*[graph->v + 1](); 
                    graph->H = new ELEMENT[graph->v + 1];

                    // initializing node value for each H[i]
                    for(int i = 1; i <= graph->v; i++) 
                        graph->H[i].node = i;
                        
                    int count = 0, neighbor = 0, weight = 0;
                    while(inputFile >> vertices) { // While file is still
                                                   // reading

                        if(count < graph->e) { // Makes sure that no more than
                                               // graph->e # of edges get added
                            count++;
                            struct LIST* newList = new LIST;

                            inputFile >> neighbor; // Reading in neighbor
                            inputFile >> weight; // REading in weight

                            // Initializing values for new LIST object
                            newList->neighbor = neighbor;
                            newList->weight = weight;
                            newList->next = NULL;

                            // tempList points to head of A at index "vertices"
                            struct LIST* tempList = graph->A[vertices];

                            if(tempList == NULL) { // If list is empty add
                                                   // add new list to head

                                graph->A[vertices] = newList;
                            }
                            else {
                                // Iterate to end of list and add new list
                                while(tempList->next != NULL) 
                                    tempList = tempList->next;        

                                tempList->next = newList;
          
                            }   
                        }
                    }

                    if(count < graph->e) {
                        cout << "Error: The number of edges is less than" <<
                            " as specified in the beginning of the file." <<
                            endl;

                        fileRead = false; // File wasnt read properly

                        // Deleting H array
                        delete[] graph->H;
                        graph->H = NULL;
                        
                        // Deleting linked list at each A index
                        for(int i = 1; i <= graph->v; i++) {
                            struct LIST* head = graph->A[i];
                            struct LIST* temp = head;

                            while(temp != NULL) {
                                temp = temp->next;
                                delete head;
                                head = NULL;
                                head = temp;
                            }
                        }
                        
                        // Deleting A array
                        delete[] graph->A;
                        graph->A = NULL;

                    }

                    inputFile.close();
                }
                else
                    cout << "There was a problem opening file Ginput.txt" <<
                        " for reading." << endl;
                break;
                    

            default: 
                break;
        }
    }  
   
    // Deleting H array
    delete[] graph->H;
    graph->H = NULL;
                        
    // Deleting linked list at each A index
    for(int i = 1; i <= graph->v; i++) {
        struct LIST* head = graph->A[i];
        struct LIST* temp = head;

        while(temp != NULL) {
            temp = temp->next;
            delete head;
            head = NULL;
            head = temp;
        }
    }
                        
   // Deleting A array
   delete[] graph->A;
   graph->A = NULL;

   delete graph;
   graph = NULL;
    
    exit(0); // End program
}

