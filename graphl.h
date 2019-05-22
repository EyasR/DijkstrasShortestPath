// ----------------------------- graphl.cpp/h ----------------------------------
// Eyas Rashid Assignment 3, CSS 343 B, Spring 2019
// Created on: 07/05/2019
// Last Modified on: 14/05/2019
// -----------------------------------------------------------------------------
// Purpose: GraphL class calculates depth-first search algorithm
// from data file provided and prints out all information in object
// -----------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions:
// assumes the correct data file is provided and formatted as described in specs
// ------------------------------------------------------------------------------

#ifndef ASG3_EYASRASHID_GRAPH1_H
#define ASG3_EYASRASHID_GRAPH1_H

#include "nodedata.h"
#include <iostream>
#include <fstream>

using namespace std;

typedef int Node;

int const MAXNODES_LIST = 100;  // const size of an array

class GraphL {
public:
    // Constructor
    GraphL();

    // Destructor
    ~GraphL();

    // Member Functions
    void buildGraph(ifstream&);
    void depthFirstSearch();
    void displayGraph();

private:

   int size;
   struct EdgeNode;               // struct declaration
   struct GraphNode {
        EdgeNode* edgeHead;        // head of the list of edges
        NodeData* data;            // data information about each node
        bool visited;
    };
    GraphNode node_array[MAXNODES_LIST];

    struct EdgeNode {
        int adjGraphNode;           // subscript of the adjacent graph node
        EdgeNode* nextEdge;         // next node
    };

    // Delete object
    void makeEmpty();

    // Helper function
    void depthFirstSearchHelper(int v);
};


#endif //ASG3_EYASRASHID_GRAPH1_H
