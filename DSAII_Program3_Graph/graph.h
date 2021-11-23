/*

Jaewon Cho DSA Program 3 graph.h
This header file defines the graph class

*/

#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <string>
#include <list>
#include "heap.h"

using namespace std;

class graph{
	public:
		// Constructor that initializes Hash Table for
		// the graph
		graph();

		// Inserts nodes into the graph 
		void insert(const string &input);

		// Checks to see if graph contains the specified node
		// Returns true if graph does contain node
		bool contains(const string &id);

		// Performs Dijkstra's Algorithm on a starting node
		void dijkstra(const string &id);

		// Outputs the paths from nodes to a user specified file
		void output(const string &file);

	private:

		int size;
		class node;

		class edge{
			public:
				int cost;	// weight of the edge
				node *next;	// Points to node next node 
		};
		
		class node{
			public:
				string id;
				list<edge> adjList;		// Adjacency List implementation
				list<string> path;	// List to store the path taken
				bool visited;
				int distance;	// Distance from starting node to current node
		}; 

		list<node *> nodeList;
		hashTable *mapping;
};

#endif