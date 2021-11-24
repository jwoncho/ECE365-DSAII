/*

Jaewon Cho DSA Program 3 graph.cpp

*/

#include "graph.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iterator>
#include <limits.h>
#define VERTEX 512 // To set size of hashTable

using namespace std;

// Constructor for graph class
graph::graph(){
	size = 0;
	mapping = new hashTable(VERTEX);
}

// Inserts nodes into the graph 
void graph::insert(const string &input){
	string line, id1, id2, weight;
	node *node1, *node2;
	edge e;

	// sperates the string into its proper tokens
	istringstream iss(input);
	iss >> id1 >> id2 >> weight;

	// First node
	if (mapping -> contains(id1))
		node1 = (node *)mapping -> getPointer(id1);
	else{
		node1 = new node;
		node1 -> id = id1;
		node1 -> visited = false;
		node1 -> distance = INT_MAX;
		nodeList.push_back(node1);
		mapping -> insert(id1, node1);
		size++;
	}

	// Second node
	if (mapping -> contains(id2))
		node2 = (node *)mapping -> getPointer(id2);
	else{
		node2 = new node;
		node2 -> id = id2;
		node2 -> visited = false;
		node2 -> distance = INT_MAX;
		nodeList.push_back(node2);
		mapping -> insert(id2, node2);
		size++;
	}

	// Connecting the nodes
	e.cost = stoi(weight);
	e.next = node2;
	node1 -> adjList.push_back(e);
}

// Checks to see if graph contains the specified node
// Returns true if graph does contain node
bool graph::contains(const string &id){
	return (mapping -> contains(id));
}

// Performs Dijkstra's Algorithm on a starting node
void graph::dijkstra(const string &id){
	heap dHeap(size);

	// Sets the starting node in both the path list and the heap
	node *start = (node *) mapping -> getPointer(id);
	start -> distance = 0;
	start -> path.push_back(id);
	dHeap.insert(id, start -> distance, start);

	
	// Insert the remaining nodes
	for (list<node *>::const_iterator iter = nodeList.begin(); iter != nodeList.end(); iter++){
		if ((*iter) -> id != id)
			dHeap.insert((*iter) -> id, (*iter) -> distance, *iter);
	}


	// Dijkstra algorithm
    // Implementation inspired by Figure 9.31 in our textbook
	for (int i = 0; i < size; i++){
		node *temp;
		dHeap.deleteMin(NULL, NULL, &temp);
		for (list<edge>::const_iterator iter = temp->adjList.begin(); (iter != temp->adjList.end()) && (temp -> distance != INT_MAX); iter++){
			// Checks for both conditions
            if ((iter->cost + temp->distance) < (iter->next->distance)	&&	(iter->next->visited == false)){
				// Update the distance and the heap
				iter->next->distance = (iter->cost + temp->distance);
				dHeap.setKey(iter->next->id, iter->next->distance);

				// Update the path list 
				iter->next->path = temp->path;
				iter->next->path.push_back(iter->next->id);
			}
		}

		temp->visited = true;
	}
}

// Outputs the paths from nodes to a user specified file
void graph::output(const string &file){
	ofstream outfile;
	outfile.open(file);

	for(list<node *>::const_iterator iter = nodeList.begin(); iter != nodeList.end(); iter++){
		if ((*iter)->distance == INT_MAX)
			outfile << (*iter)->id << ": NO PATH" << endl;
		else{
			outfile << (*iter)->id << ": " << (*iter)->distance << " [";
			for (list<string>::const_iterator iter2 = (*iter)->path.begin(); iter2 != --(*iter)->path.end(); iter2++)
				outfile << *iter2 << ", ";

			outfile << (*iter)->path.back() << "]" << endl;
		} 
	}

	outfile.close();
}