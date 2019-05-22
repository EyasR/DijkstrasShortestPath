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

#ifndef ASG3_EYASRASHID_GRAPHM_H
#define ASG3_EYASRASHID_GRAPHM_H

#include "nodedata.h"
#include <fstream>
#include <iostream>

using namespace std;

typedef int Node;
typedef int Weight;


// constant size for T and C table
int const MAXNODES_MATRIX = 100;


class GraphM {
public:
    // Constructor
    GraphM();

    // Member Functions
    void buildGraph(ifstream&);
    bool insertEdge(int fromNode, int toNode, int distance);
    bool removeEdge(int fromNode, int toNode);
    void findShortestPath();
    void displayAll();
    void display(int fromNode, int toNode);

private:
    struct TableType {
        bool visited;                       // whether node has been visited
        int dist;                           // shortest distance from source known so far
        int path;                           // previous node in path of min dist
    };

    NodeData data[MAXNODES_MATRIX];                   // data for graph nodes
    int C[MAXNODES_MATRIX][MAXNODES_MATRIX];          // cost array, the adjacency matrix
    int size;                                         // number of nodes in the graph
    TableType T[MAXNODES_MATRIX][MAXNODES_MATRIX];    // stores visited, distance, path

    //Helper functions
    void findData(int fromNode, int toNode);
    void findPath(int fromNode, int toNode);
};



#endif //ASG3_EYASRASHID_GRAPHM_H
