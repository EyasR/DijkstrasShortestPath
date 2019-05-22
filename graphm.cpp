// ----------------------------- graphm.cpp/h ----------------------------------
// Eyas Rashid Assignment 3, CSS 343 B, Spring 2019
// Created on: 07/05/2019
// Last Modified on: 14/05/2019
// -----------------------------------------------------------------------------
// Purpose: Creates a ADS graph using an adjacency matrix. Capable of building,
// destructing, and modifying said graph. Performs Dijkstra's algorithm between
// any given nodes in a graph (all paths or shortest paths)
// -----------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions:
// assumes the correct data file is provided and formatted as described in specs
// ------------------------------------------------------------------------------

#include "graphm.h"
#include "limits.h"
#include <iomanip>

// --------------------- Default Constructor --------------------
// Constructs an adjacency matrix with all values set to INT_MAX
// --------------------------------------------------------------
GraphM::GraphM() {

    size = 0;

    for (int row = 1; row < MAXNODES_MATRIX; row++){

        for (int column = 1; column < MAXNODES_MATRIX; column++){
            C[row][column] = INT_MAX;
            T[row][column].dist = INT_MAX;
            T[row][column].path = 0;
            T[row][column].visited = false;
        }
    }
} // end of GraphM

// --------------------- buildGraph -----------------------------
// Builds up graph node information and adjacency matrix of edges
// from text file
// --------------------------------------------------------------
void GraphM::buildGraph(ifstream& infile1)
{
    //first, reads in the number of nodes into size
    infile1 >> size;
    string nodeName = "";           // name of each node
    getline(infile1, nodeName);     // read line

    for (int i = 1; i <= size; ++i){
        // assigns node names
        data[i].setData(infile1);
    }

    int fromNode;
    int toNode;
    int distance;

    infile1 >> fromNode >> toNode >> distance;

    while ( fromNode != 0){
        C[fromNode][toNode] = distance;
        infile1 >> fromNode >> toNode >> distance;

    }

} // end of buildGraph

// --------------------- findShortestPath -----------------------
// Finds the shortest path between every node to every other node
// in the graph using Dijkstra's algorithm
// --------------------------------------------------------------
void GraphM::findShortestPath() {
    for (Node sourceNode = 1; sourceNode <= size; sourceNode++) {
        T[sourceNode][sourceNode].dist = 0;
        T[sourceNode][sourceNode].visited = true;

        // find adjacent neighboring nodes
        for (Node i = 1; i <= size; i++) {

            if (C[sourceNode][i] != INT_MAX) {
                T[sourceNode][i].dist = C[sourceNode][i];
                T[sourceNode][i].path = sourceNode;
            }
        }

        int v = 0;  // smallest vertex

        // find smallest weight
        do {
            int minimum = INT_MAX;
            v = 0;

            // find closest child and continue search
            for (Node n = 1; n <= size; n++){

                if (!T[sourceNode][n].visited && (C[sourceNode][n] < minimum)) {

                    minimum = C[sourceNode][n];
                    v = n;
                }
            }

            if (v == 0)
                break;

            // checks node as visited
            T[sourceNode][v].visited = true;

            for (Node w = 1; w <= size; ++w) {
                if (T[sourceNode][w].visited)
                    continue;

                if (C[v][w] == INT_MAX)
                    continue;

                if (v == w)
                    continue;

                if (T[sourceNode][w].dist > T[sourceNode][v].dist + C[v][w]) {

                    T[sourceNode][w].dist = T[sourceNode][v].dist + C[v][w];
                    T[sourceNode][w].path = v;
                }
            }
        }

        while (v != 0); // end loop
    }
} // end of findShortestPath

// --------------------- insertEdge -----------------------------
// Inserts an edge into a graph between 2 given nodes
// --------------------------------------------------------------
bool GraphM::insertEdge(Node fromNode, Node toNode, Weight distance) {

    // checks toNode make sure insert is legal
    if (toNode > size || toNode < 1)
        return false;

    if (fromNode > size || fromNode < 1)
        return false;

    if (distance != 0 && fromNode == toNode)
        return false;

    if (distance < 0)
        return false;

    // insert edge
    C[fromNode][toNode] = distance;

    // re-run Dijkstra's Algorithm with newly inserted edge
    findShortestPath();

    return true;
} // end of insertEdge

// ----------- removeEdge --------------------
// Removes an edge between two nodes
// -------------------------------------------
bool GraphM::removeEdge(Node fromNode, Node toNode) {
    // check toNode make sure remove is legal
    if (fromNode > size || fromNode < 1)
        return false;

    if (toNode > size || toNode < 1)
        return false;

    // remove edge
    C[fromNode][toNode] = INT_MAX;

    // re-run Dijkstra's Algorithm with newly removed edge
    findShortestPath();

    return true;
} // end of removeEdge

// --------------------- displayAll------------------------------
// Uses couts to demonstrate that the algorithm works properly
// --------------------------------------------------------------

void GraphM::displayAll() {
    // print table titles for readout
    cout << "Description" << setw(20) << "From node" << setw(10) << "To node"
         << setw(14) << "Dijkstra's" << setw(7) << "Path" << endl;

    for (Node fromNode = 1; fromNode <= size; fromNode++) {
        cout << data[fromNode] << endl << endl;     // print node name

        for (Node toNode = 1; toNode <= size; toNode++) {
            if (T[fromNode][toNode].dist != 0) {
                cout << setw(27) << fromNode;   // print fromNode node
                cout << setw(10) << toNode;     // print toNode node

                if (T[fromNode][toNode].dist == INT_MAX)
                    cout << setw(12) << "----" << endl; // no adjacent nodes

                else {
                    cout << setw(12) << T[fromNode][toNode].dist;   // print distance
                    cout << setw(10);

                    findPath(fromNode, toNode); // call helper
                    cout << endl;
                }
            }
        }
    }
} // end of displayAll

// --------------------- display() -----------------------------------------
// Uses couts to display the shortest distance with path info between the
// fromNode to the toNode
// --------------------------------------------------------------
void GraphM::display(Node fromNode, Node toNode){
    //check if edge exist
    if ((fromNode > size || fromNode < 0) || (toNode > size || toNode < 0)){
        // print node data
        cout << setw(7) << fromNode << setw(7) << toNode;
        // no edge
        cout << setw(15) << "----" << endl;

        return;
    }
    // print node fromNode and toNode data
    cout << setw(7) << fromNode << setw(7) << toNode;

    // check adjacent node
    if (T[fromNode][toNode].dist != INT_MAX) {
        // prints out distance
        cout << setw(12) << T[fromNode][toNode].dist << setw(15);

        findPath(fromNode, toNode);
        cout << endl;

        findData(fromNode, toNode);
    }

    // no adjacent node
    else{
        cout << setw(15) << "----" << endl;
    }

    cout << endl;
} // end of display

// --------------------- findData() -----------------------------------------
// Helper function for display()
// Recursively finds data for the given edge distance
// --------------------------------------------------------------
void GraphM::findData(Node fromNode, Node toNode){

    // no data
    if (T[fromNode][toNode].dist == INT_MAX)
        return;

    // print data
    if (fromNode == toNode){
        cout << data[toNode] << endl;
        return;
    }

    // assign toNode node toNode nodeData
    Node nodeData = toNode;

    findData(fromNode, toNode = T[fromNode][toNode].path);

    cout << data[nodeData] << endl << endl;
} // end of findData

// --------------------- findPath() -----------------------------------------
// Helper function for display() and displayAll()
// Recursively finds path for a given edge
// --------------------------------------------------------------
void GraphM::findPath(Node fromNode, Node toNode){
    // print data
    if (fromNode == toNode){
        cout << toNode << " ";
        return;
    }
    // no path exists
    if (T[fromNode][toNode].dist == INT_MAX)
        return; // no path


    Node pathData = toNode;
    findPath(fromNode, toNode = T[fromNode][toNode].path);
    // print out path
    cout << pathData << " ";
} // end of findPath