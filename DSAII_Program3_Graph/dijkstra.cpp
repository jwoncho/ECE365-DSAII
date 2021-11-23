/*

Jaewon Cho DSA Program 3 dijkstra.cpp

*/

#include "graph.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iterator>

using namespace std;

// Gets the name of the input file and starting vertex and runs the Dijkstra Algorithm
// Ouputs the path to the file specified by user
int main(){
	string fin, fout, line, vertex;
	graph g;

	cout << "Enter name of graph file: ";
	cin >> fin;

	ifstream input(fin.c_str());

	// Inserts each line into the graph
	if (input.is_open())
	{
		while (getline(input, line))
			g.insert(line);

		input.close();
	}

	// Asks user for valid vertex 
	do {
		cout << "Enter a valid vertex id for the starting vertex: ";
		cin >> vertex;

	} while (g.contains(vertex) == false);

	// Runs Dijkstra and measures the time it takes
	clock_t t1 = clock();
	g.dijkstra(vertex);
	clock_t t2 = clock();

	double diff = ((double)(t2 - t1)) / CLOCKS_PER_SEC;
	cout << "Run time of Dijkstra Algorithm: " << diff << endl;


	// Outputs path to specified file
	cout << "Enter name of output file: ";
	cin >> fout;
	g.output(fout);

	return 0;
}