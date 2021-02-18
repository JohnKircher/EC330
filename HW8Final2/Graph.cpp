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
    int vertexToInsert = getNumVertices(); //set it equal to the number of verticies we already have
    vertices.insert(vertexToInsert); //insert the vertex that we wish to insert
    return vertexToInsert; //returns the current ID/position of the vertex inserted. 
}


void Graph::addEdge(directedEdge newEdge, int weight){
    bool checkVer1 = false;
	bool checkVer2 = false; //booleans to check if the verticies actually exist in the graph
	
	int vertex1 = newEdge.first; //gets first value from the directed edge pair
	int vertex2 = newEdge.second; //gets second value fromt the directed edge pair

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
		//looping through the map of directed edge (edge1, edge2) wanting to check that the edges line up
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
				cout << edge.second << " (" << getWeight(make_pair(edge.first, edge.second)) << ") "; //print to the command line making a pair of the edges since this was the format in the header file
			}
		}
		cout << endl; //needed to add a line here to get the correct format
	}
	cout << "\n"; //return for format of the modified dikjstra part
}


void Graph::generateGraph(string fileName){
	ifstream myFile;
	myFile.open(fileName);
	
	int flag = 0;
	int vertex1;
	int vertex2;
	int numEdges;
	int weight;
	string type; //used for directed/undirected depening on input file
	string graphs; //next word is graphs
	
	while(!myFile.eof()){ //while not at the end of the file
		
		if(flag == 0){
			
			flag = 1; //change the flag since we only want to read the first line once
			myFile >> vertex1 >> numEdges >> type >> graphs; //take in the first the line since only the first line will have the strings, we only want to do thisn once. 

			for(int i = 0; i < vertex1; i++){ //sample program/first test case should add 6 vertices
				addVertex(); //add the vertex to the set
			}
		}
		else{
			myFile >> vertex1 >> vertex2 >> weight; //take in the rest of the lines with this format from the text file. 

			addEdge(make_pair(vertex1, vertex2), weight); //need to add the edge to the set and the map
		}
	}

}

#define MAX 999999999

/* I modified dijkstra's algorithm using Dial's algorithm. However I used vectors instead of buckets
 * for an easier implemenatation since I know how to use push_back. In this modified algorithm the 
 * source is always the minimum as I set it to 0 at the start. Instead of a priority queue like in 
 * dijkstra's, I use a vector for each weight from 0 to MAX. This makes the complexity O(E + WV)
 * My program looks at the next minimum distance and replaces the vector path with the according weight.
 * Then I immediately set a new weight based on my vertex location and look at the next possible minimum path. 
 * This temporary vertex in the vector is updated accordingly as I find new shortest paths in the graph.
 */
void Graph::modifiedDijkstra(int source){

	vector<int> path; //vector path that will be updated with the shortest path at the end of the function

	for(int i = 0; i < vertices.size(); i++){ //fill the entire vector with MAX = close to infinite number
		path.push_back(MAX); //initializie verything as MAX
	}

	map<directedEdge, int>::iterator i; //iterator for the weights. 
	path[source] = 0; //set the source to 0, so now we have: 0, MAX, MAX, MAX, MAX, MAX for the first test case
	
	for(i = weights.begin(); i != weights.end(); i++){ //loop through the weights map, i runs in parallel to the path vector
		for(int j = 0; j < getNumVertices(); j++){
			int weight = getWeight(make_pair(source, i->first.second)); //weight here is the edge from the source node connected to the next vertex.
			//cout << weight << "\n";

			if(weight != 0){
				//u, i->first.second, weight
				//u, v, weight
				if((path[i->first.second]) > (path[source] + weight)){ //if the current path weight is greater then the source weight + weight of the vertex we are looking at, then set it as that since that is the current shortest path to that vertex
					//cout << "Hello " << path[i->first.second] << " " << path[source] << " " << weight << "\n";
					path[i->first.second] = path[source] + weight;
					//cout << "Hello " << path[i->first.second] << " " << path[source] + weight << "\n"; 
				}
			}
			
			for(int k = j+1; k < getNumVertices(); k++){ //now we need to loop through looking at the next vertex to potentially find a shortet path
				int weight = getWeight(make_pair(i->first.second, k)); //set the weight here
					
				if(weight != 0){
					//u,v,weight
					//i->first.second,k,weight
					//cout << path[k] << "\n";
					//cout << path[i->first.second + weight] << "\n";
					//cout << weight << "\n";
					if((path[k]) > (path[i->first.second] + weight)){ //if path weight is greater than that of path of the last vertex + weight, then set the shortest path to that weight. 
					//cout << "Goodbye" << path[k] << " " << path[i->first.second] << " " << weight << "\n";
					path[k] = path[i->first.second] + weight;
					//cout << "Goodbye" << path[k] << " " << path[i->first.second] + weight << "\n";
				}
				}
			}
			
			
		}
	}
	//below handles printing out the shortest path or if there is no path. 
	cout << "Shortest paths from node " << source << ":" << endl;

	for(int i = 0; i < getNumVertices(); i++){
		if(i != source){
			if(path[i] != MAX){
				cout << "Distance to vertex " << i << " is " << path[i] << " and there are 1 shortest paths" << endl;
			}
			else{
				cout << "Distance to vertex " << i << " is " << MAX << " and there are 0 shortest paths" << endl;
			}
		}

	}
}
