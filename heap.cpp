#include "heap.h"

using namespace std;

// Heap() constructor 
Heap::Heap(){}

// Returns index of parent of the element at index i
int Heap::PARENT(int i) 
{
    return (i / 2);
}

// Returns left child of element at index i
int Heap::LEFT(int i)
{
    return (2 * i);
}

// eturns right child of element at index i
int Heap::RIGHT(int i)
{
    return (2 * i + 1);
}


// Method to maintain the heap property of the array
void Heap::min_heapify(GRAPH* heap, int i) 
{
    int smallest = 0; // Specifies index of smallest element
    int l = LEFT(i);
    int r = RIGHT(i);

    // Checking whether left child is less than parent
    if(l <= heap->v && heap->H[l].d < heap->H[i].d)
        smallest = l;
    else
        smallest = i;

    // Checking whether right child is less than element at index smallest
    if(r <= heap->v && heap->H[r].d < heap->H[smallest].d)
        smallest = r;

    // If element at index smallest is not parent, exchange parent element
    // with element at index smallest and call HEAPIFY recursively to maintain
    // heap property.
    if(smallest != i) {
        
        // Exchanging larger distance with smaller
        int parent = heap->H[i].p;
        int num = heap->H[i].d;
        int node = heap->H[i].node;

        heap->H[i].d = heap->H[smallest].d;
        heap->H[i].p = heap->H[smallest].p;
        heap->H[i].node = heap->H[smallest].node;

        heap->H[smallest].node = node;
        heap->H[smallest].d = num;
        heap->H[smallest].p = parent;

        min_heapify(heap, smallest); // Apply heapify again to maintain min-heap property
    }

}


// Deletes the element with minimum distance and returns it to caller
ELEMENT Heap::DeleteMin(GRAPH* heap)
{

    // Deleting min element if the heap contains no elements
    if(heap->v < 1)
    {
        cout << "There are no elements in the heap to delete." << endl;

        ELEMENT null;
        return null;
    }
    else
    {
        // Make sure that element to delete is the one with the
        // shortest distance
        for(int i = (heap->v)/2; i >= 1; i--)
            min_heapify(heap, i); 

        ELEMENT min = heap->H[1]; // min is the minimum distance element
       
        // Replacing element at H[1] with element at end of heap
        heap->H[1].node = heap->H[heap->v].node;
        heap->H[1].d = heap->H[heap->v].d;
        heap->H[1].p = heap->H[heap->v].p;
        heap->v--;

        min_heapify(heap,1); // Maintain min-heap

        return min;
    }
}



// Prints out graph
void Heap::printHeap(GRAPH* heap)
{
    cout << heap->v << " " << heap->e << endl;
    
    for(int i = 1; i <= heap->v; i++)
    {
        struct LIST* tempList = heap->A[i];
        cout << heap->H[i].node << " : ";
        
        while(tempList != NULL) {

            if(tempList->next == NULL) {
                cout << "(" << tempList->neighbor << ", " << tempList->weight <<
                ")";
            }
            else {
                cout << "(" << tempList->neighbor << ", " << tempList->weight <<
                "); ";
            }
            tempList = tempList->next;
        }
        cout << endl;
    }
}
