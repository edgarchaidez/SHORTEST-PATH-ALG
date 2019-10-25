#ifndef _HEAP_H_
#define _HEAP_H_

#include <iostream>
#include "graph.h"

class Heap {

private:

    // Helper functions
    int PARENT(int i);
    int LEFT(int i);
    int RIGHT(int i);
    void min_heapify(GRAPH* heap, int i);
    
public:

    Heap(); // constructor
 
    //Module functions
    ELEMENT DeleteMin(GRAPH* heap);
    void printHeap(GRAPH* heap);
};

#endif



