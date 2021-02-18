#include "Graph.h"
#include <set>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

Graph::Graph(void){
}

int Graph::addVertex(void){
    if(vertices.size() == 0){
        vertices.insert(0);
        return 0;
    }
    else{
        int last = vertices.size() - 1;
        vertices.insert(last+1);
        return last + 1;
    }
}

void Graph::addEdge(directedEdge newEdge, int weight){
    int v1 = newEdge.first;
    int v2 = newEdge.second;
    bool v1correct = false;
    bool v2correct = false;

    for (set<int>::iterator i = vertices.begin(); i != vertices.end(); i++){
		int vertex = *i;
		if (vertex == v1){
			v1correct = true;
		}
		if (vertex == v2){
			v2correct = true;
		}
	}

    if(v1correct && v2correct){
        edges.insert(newEdge);
        weights.insert(pair <directedEdge,int> (newEdge, weight));
    }
}

int Graph::getNumVertices(void){
    int num = vertices.size();
    return num;
}

int Graph::getWeight(directedEdge edge){
    int v1 = edge.first;
	int v2 = edge.second;
	for (map <directedEdge, int>::iterator i = weights.begin(); i != weights.end(); i++){
		int vertex1 = (*i).first.first;
		int vertex2 = (*i).first.second;
		int fat = (*i).second;
		if (v1 == vertex1 && v2 == vertex2){
			return fat;
		}
	}
	return -1;
}

bool Graph::isEdge(directedEdge newEdge){
    	int v1 = newEdge.first;
	int v2 = newEdge.second;
	for (set<directedEdge>::iterator i = edges.begin(); i != edges.end(); i++){
		int vertex1 = (*i).first;
		int vertex2 = (*i).second;
		if (v1 == vertex1 && v2 == vertex2){
			return true;
		}
	}
	return false;
}

void Graph::print(){
	for (set<int>::iterator i = vertices.begin(); i != vertices.end(); i++){
		int vertex = *i;
		cout << vertex << ": ";
		for (set<directedEdge>::iterator j = edges.begin(); j!=edges.end();j++){
			directedEdge edge=*j;
			int v1 = edge.first;
			int v2 = edge.second;
			if (v1 == vertex){
				cout << v2 <<" ";
				for (map <directedEdge, int>::iterator k = weights.begin(); k!=weights.end(); k++){
					pair <directedEdge, int> wat = *k;
					int firstv = wat.first.first;
					int secondv = wat.first.second;
					int printweight = wat.second;
					if (v1 == firstv && v2 == secondv){
						cout << "(" << printweight << ")" << " ";
					}
				}
				
			}

		}
		cout << endl;
	}
}

void Graph::generateGraph(string fileName){
    string line;
    ifstream file(fileName);
    bool firstline = true;

    if(file.is_open()){
        while(getline(file,line)){
            if(firstline == true){
                string numVerticies;
                int i;
                for(i = 0; i < line.size(); i++){
                    if(line[i] != ' '){
                        numVerticies.push_back(line[i]);
                    }
                    else{
                        break;
                    }
                }
                int numVerticiesInt;
                stringstream geek(numVerticies);
                geek >> numVerticiesInt;
                for(int j = 0; j < numVerticiesInt; j++){
                    addVertex();
                }
            }
            else{
                int k;
                string v1;
                string v2;
                string W;
                for(k = 0; k < line.size(); k++){
                    if(line[k] != ' '){
                        v1.push_back(line[k]);
                    }
                    else{
                        break;
                    }
                }
                for(k = (k+1); k < line.size(); k++){
                    if(line[k] != ' '){
                        v2.push_back(line[k]);
                    }
                    else{
                        break;
                    }
                }
                for(k = (k+1); k < line.size(); k++){
                    W.push_back(line[k]);
                }
                int v1int;
                int v2int;
                int Wint;
                stringstream geek1(v1);
                geek1 >> v1int;
                stringstream geek2(v2);
		geek2 >> v2int;
                stringstream geekW(v2);
		geekW >> Wint;
                directedEdge addingedge;
		addingedge = make_pair(v1int,v2int);
		addEdge(addingedge,Wint);

            }
            firstline = false;
        }
        file.close();
    }
}

