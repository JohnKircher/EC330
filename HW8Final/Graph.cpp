#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm> 
#include "Graph.h"

using namespace std;

Graph::Graph(){ //default constructor with no edges or verticies

}


int Graph::addVertex(){
    int vertexToInsert = getNumVertices();
    vertices.insert(vertexToInsert); //insert the vertex that we wish to insert
    return vertexToInsert;
}


void Graph::addEdge(directedEdge newEdge, int weight){
    	bool checkVer1 = false;
	bool checkVer2 = false; //booleans to check if the verticies actually exist in the graph
	
	int vertex1 = newEdge.first;
	int vertex2 = newEdge.second;

	set<int>::iterator i;

	for(i = vertices.begin(); i != vertices.end(); i++){ //looping through the verticies
		int vertex = *i;
		
		if(vertex == vertex1){ //if vertex1 matches, then set the marker to true
			checkVer1 = true;
		}
		if(vertex == vertex2){ //if vertex2 matches, then set its marker to true
			checkVer2 = true;
		}
	}
	if((checkVer1 == true) && (checkVer2 == true)){ //once we are sure both verticies exist we can insert the new edge as well as make the piar
		edges.insert(newEdge);
		weights.insert(pair<directedEdge,int> (newEdge, weight));
	}

    
}


int Graph::getNumVertices(){
    return vertices.size(); //simply return the size of verticies which is the number of verticies
}


int Graph::getWeight(directedEdge edge){
	map<directedEdge, int>::iterator i;

	for(i = weights.begin(); i != weights.end(); i++){ //loop through all the weights in the map
		if((i->first.first == edge.first) && (i->first.second == edge.second)){ //while looking at the pair we check to see if we have the correct edges, if we do then we can return the weight.
			return i->second; //return the second element since we know this is the weight
		}
	}
	return 0;
}


bool Graph::isEdge(directedEdge newEdge){
	set<directedEdge>::iterator i;

	int vertex1 = newEdge.first;
	int vertex2 = newEdge.second;

	for(i = edges.begin(); i != edges.end(); i++){ //loop through the edges
		int compareVertex1;
		int compareVertex2;

		compareVertex1 = (*i).first; //using i pointer, we want to check that the edge in the graph indeed has the same verticies as the newEdge
		compareVertex2 = (*i).second;
		
		if((vertex1 == compareVertex1) && (vertex2 == compareVertex2)){ //does the edge in the graph have the same verticies as the new edge?
			return true; //if so, then return true
		}
	}
	return false; //o/w false
}


void Graph::print(){
	set<int>::iterator i;  //iterator used for verticies, i
	set<directedEdge>::iterator j; //iterator used for edges, j

	for(i = vertices.begin(); i != vertices.end(); i++){ //first loop through the verticies
		cout << *i << ": ";
		for(j = edges.begin(); j != edges.end(); j++){ //loop through the edges
			
			directedEdge edge = *j; //set each edge depending on the vertex that we are at from the first loop 

			if(edge.first == *i){ //once we have the correct edge at that vertex we need to print it to the adjacenecy list. 
				cout << edge.second << "(" << getWeight(make_pair(edge.first, edge.second)) << ")" << " "; //print to the command line making a pair of the edges since this was the format in the header file
			}
		}
		cout << endl; //needed to add a line here to get the correct format
	}
	cout << "\n"; //return for format of the modified dikjstra part
}


void Graph::generateGraph(string fileName){
	ifstream myFile;
	myFile.open(fileName);
	
	int count = 0;
	int vertex1;
	int vertex2;
	int numEdges;
	int weight;
	string type; //used for directed/undirected depening on input file
	string graphs; //next word is graphs
	
	while(!myFile.eof()){ //while not at the end of the file
		
		if(count == 0){
			
			count++;
			myFile >> vertex1 >> numEdges >> type >> graphs; //take in the first the line since only the first line will have the strings, we only want to do thisn once. 

			for(int i = 0; i < vertex1; i++){
				addVertex(); //add the vertex to the set
			}
		}
		else{
			myFile >> vertex1 >> vertex2 >> weight; //take in the rest of the lines with this format from the text file. 

			addEdge(make_pair(vertex1, vertex2), weight); //need to add the edge to the set and the map
		}
	}

}
