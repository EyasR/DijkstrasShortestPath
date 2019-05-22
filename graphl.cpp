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
#include "graphl.h"
#include <iomanip>

// --------------------- GraphL -------------
// constructor
// ------------------------------------------
GraphL::GraphL(){
    size = 0;

    for (Node i = 1; i < MAXNODES_LIST; ++i){
        node_array[i].edgeHead = NULL;
        node_array[i].data = NULL;
        node_array[i].visited = false;
    }
} // end of GraphL

// --------------------- ~GraphL ----------------
// Destructor
// ----------------------------------------------
GraphL::~GraphL(){
    makeEmpty();
} // end of ~GraphL

// --------------------- makeEmpty -----------------------------
// Deletes object
// -------------------------------------------------------------
void GraphL::makeEmpty(){
    for (Node x = 1; x <= size; ++x){
        node_array[x].visited = false;
        delete node_array[x].data;  // delete edge name
        node_array[x].data = NULL;  // set edge name to NULL

        // check for linked list in array index
        if (node_array[x].edgeHead != NULL){
            EdgeNode* deleteEdgeNode = node_array[x].edgeHead;

            // traverse linked list

            while (deleteEdgeNode != NULL){
                node_array[x].edgeHead = node_array[x].edgeHead->nextEdge;
                delete deleteEdgeNode; // delete node
                deleteEdgeNode = node_array[x].edgeHead;   // move head
            }
        }
    }
} // end of makeEmpty

// --------------------- buildGraph -----------------------------------------
// Builds up graph node adjacency list using infile (text file)
// --------------------------------------------------------------------------
void GraphL::buildGraph(ifstream& infile2){
    // read from data file
    infile2 >> size;            // sets the size
    string nodeName = "";       // name of each node
    getline(infile2, nodeName); // read line

    // insert edge names
    for (int i = 1; i <= size; ++i){
        getline(infile2, nodeName);
        NodeData* tempData = new NodeData(nodeName);

        // inserts node into array
        node_array[i].data = tempData;
    }

    Node fromNode;
    Node toNode;

    // fills in linked list
    while (infile2 >> fromNode >> toNode){
        if (fromNode == 0)
            break;

        // first node at array index
        if (node_array[fromNode].edgeHead == NULL){
            EdgeNode* node = new EdgeNode;
            // insert adjacent
            node->adjGraphNode = toNode;
            // point toNode head
            node_array[fromNode].edgeHead = node;
            node_array[fromNode].edgeHead->nextEdge  = NULL;
        }

        // additional nodes in linked list
        else {
            EdgeNode* node = new EdgeNode;
            // insert adjacent node
            node->adjGraphNode = toNode;
            // shift pointer
            node->nextEdge = node_array[fromNode].edgeHead;
            // assign as head
            node_array[fromNode].edgeHead = node;
        }
    }
} // end of buildGraph

// --------------------- depthFirstSearch --------------------------------
// Depth-first search of graph and displays each node in depth-first order
// -----------------------------------------------------------------------
void GraphL::depthFirstSearch(){
    cout << "Depth-first ordering:";

    for (int v = 1; v <= size; ++v){

        // check if node has been visited
        if (!node_array[v].visited)
            depthFirstSearchHelper(v);
    }

    cout << endl;
} // end of depthFirstSearch

// --------------------- depthFirstSearchHelper -----------------
// Recursively finds the depthFirstSearch
// --------------------------------------------------------------
void GraphL::depthFirstSearchHelper(Node v){
    cout << setw(2) << v;   // print node
    node_array[v].visited = true;   // mark visited
    EdgeNode* current = node_array[v].edgeHead; // move pointer to head


    while (current != NULL){
        // check if visited
        if (!node_array[current->adjGraphNode].visited)
            depthFirstSearchHelper(current->adjGraphNode);

        // shifts pointer to next node in the linked list
        current = current->nextEdge;
    }
} // end of depthFirstSearchHelper

// --------------------- displayGraph ---------------------------
// Displays each node information and edge in the graph
// --------------------------------------------------------------
void GraphL::displayGraph(){

    cout << "Graph:" << endl;

    // prints out adjacency array
    for (int i = 1; i <= size; ++i){

        // prints out index and name of the currentNode
        cout << "Node" << i << "      " << *node_array[i].data << endl << endl;

        // assigns to currentNode
        EdgeNode* currentNode = node_array[i].edgeHead;

        // checks for linked list
        while (currentNode != NULL){

            // print linked list
            cout << setw(7) << "edge " << i << setw(2) << currentNode->adjGraphNode << endl;

            // shifts pointer to next node in the linked list
            currentNode = currentNode->nextEdge;
        }
    }
} // end of displayGraph