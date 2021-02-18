#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct point{
	int x;
	int y;
	int* distance;
};

struct node{
	point p;
	vector<point> plist;
};

int findPath(){
	string filename = "maze2.txt";
	vector< vector<int> > maze;
	int N = 0; //N variable for dimension size
	vector<node> adjacencyList; //adjacency list for maze
	
	ifstream myFile;
	myFile.open(filename.c_str(),ios::in);
	string line;

	
	if(myFile.is_open()){
    		while(getline(myFile,line)){
      			vector<int> newRow;
      			maze.push_back(newRow); //for each line from maze.txt make a new row
      			for(int i = 0; i < line.size(); i++){
			maze[N].push_back((int) line[i] - 48);
      			}
      			N++;
    		}
	}
	myFile.close();
	N--; 

	//adjacency list for the graph representation
	for(int i = 0; i <= N; i++){
		for(int j = 0; j <= N; j++){
			if(maze[i][j]){
				//maze[i][j] = (N+1)*(N+1) + 1; //create adjacency list
				point newPoint;
				newPoint.x = i;
				newPoint.y = j;
				newPoint.distance = &maze[i][j];
				node newNode;
				newNode.p = newPoint;
				
			
				//check for top adjacent node
				if(i != 0 && maze[i-1][j] > 0){
					point adjacencyPoint;
					adjacencyPoint.x = i-1;
					adjacencyPoint.y = j;
					adjacencyPoint.distance = &maze[i-1][j];
					newNode.plist.push_back(adjacencyPoint);
				}
				//check for bottom adjacent node
				if(i != N && maze[i+1][j] > 0){
					point adjacencyPoint;
					adjacencyPoint.x = i+1;
					adjacencyPoint.y = j;
					adjacencyPoint.distance = &maze[i+1][j];
					newNode.plist.push_back(adjacencyPoint);
				}
				//check for right adjacent node
				if(j != N && maze[i][j+1] > 0){
					point adjacencyPoint;
					adjacencyPoint.x = i;
					adjacencyPoint.y = j+1;
					adjacencyPoint.distance = &maze[i][j+1];
					newNode.plist.push_back(adjacencyPoint);
				}
				//check for left adjacent node
				if(j != 0 && maze[i][j-1] > 0){
					point adjacencyPoint;
					adjacencyPoint.x = i;
					adjacencyPoint.y = j-1;
					adjacencyPoint.distance = &maze[i][j-1];
					newNode.plist.push_back(adjacencyPoint);
				}
				adjacencyList.push_back(newNode);
			}
		}
	}
	//Set the distance at the start to 1
	if(maze[0][0] == (N+1)*(N+1) + 1){
		maze[0][0] = 1;
	}
	
    	//if the bottom right corner is 0, return 0 since impossible maze
	else if(!maze[N][N]){
		return 0;
	}
	
    	//if the top left corner is 0, return 0 since impossible maze
	else{
		return 0;
	}
    
    //Lines 110-125 incorporate an Implementation of Dijkstra's algorithm adopted and learned from GeeksforGeeks
    //https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/

	while(!(adjacencyList.empty())){
		node* min = &adjacencyList[0];
		int index = 0;
		for (int i = 1; i < adjacencyList.size();i++){
			if(*(adjacencyList[i].p.distance) < *(min->p.distance)){
				min = &adjacencyList[i];
				index = i;
			}
		}

		for(int j = 0; j < min->plist.size();j++){
			if(*(min->p.distance) < *(min->plist[j].distance)){
				*(min->plist[j].distance) = *(min->p.distance) + 1;
			}
		}
		adjacencyList.erase(adjacencyList.begin() + index);
	}

	if(maze[N][N] == (N+1)*(N+1) + 1){
		return 0;
	}
	return maze[N][N];
}

int main(){
	cout<<findPath()<<endl; 
}
