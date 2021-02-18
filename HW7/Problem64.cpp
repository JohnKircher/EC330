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

int shortestPath(string filename){

	vector< vector<int> > maze;
	int N = 0; //keep track of dimension, N will be dim - 1

	vector<node> adjList; //adjacency list will be my graph representation
	//good because constant lookup time 
	//any representation I create will have to be created in N^2 time

	ifstream inputFile;
	inputFile.open(filename.c_str(),ios::in);

	string line;

	
if(inputFile.is_open()){
    while(getline(inputFile,line)){
      vector<int> newRow;
      maze.push_back(newRow);
      
      for(int i = 0; i < line.size(); i++){
		maze[N].push_back((int) line[i] - 48);
      }
      N++;
    }
  }
	inputFile.close();
	N--; //I like it as dimension - 1

	//time to implement an adjacency list as the graph representation
	for(int i = 0; i <= N; i++){
		for(int j = 0; j <= N; j++){
			if(maze[i][j]){
				maze[i][j] = (N+1)*(N+1) + 1;
				point newPoint;
				newPoint.x = i;
				newPoint.y = j;
				newPoint.distance = &maze[i][j];
				node newNode;
				newNode.p = newPoint;
				//now check for neighbors, and at the end add newNode to adjList
			
				//check above for neighbor
				if(i != 0 && maze[i-1][j] > 0){
					point adjPoint;
					adjPoint.x = i-1;
					adjPoint.y = j;
					adjPoint.distance = &maze[i-1][j];
					newNode.plist.push_back(adjPoint);
				}
				//check below for neighbor
				if(i != N && maze[i+1][j] > 0){
					point adjPoint;
					adjPoint.x = i+1;
					adjPoint.y = j;
					adjPoint.distance = &maze[i+1][j];
					newNode.plist.push_back(adjPoint);
				}
				//check right for neighbor
				if(j != N && maze[i][j+1] > 0){
					point adjPoint;
					adjPoint.x = i;
					adjPoint.y = j+1;
					adjPoint.distance = &maze[i][j+1];
					newNode.plist.push_back(adjPoint);
				}
				//check left for neighbor
				if(j != 0 && maze[i][j-1] > 0){
					point adjPoint;
					adjPoint.x = i;
					adjPoint.y = j-1;
					adjPoint.distance = &maze[i][j-1];
					newNode.plist.push_back(adjPoint);
				}
				adjList.push_back(newNode);
			}
		}
	}
	//gotta modify distance of the source to 0
	if(maze[0][0] == (N+1)*(N+1) + 1){
		maze[0][0] = 0;
	}
	//if the bottom right corner is 0, no way to get there so return 0
	else if(!maze[N][N]){
		return 0;
	}
	//same thing with the top left corner being 0
	else{
		return 0;
	}
	//this was code to print the adjacency list that I don't want to delete
	// cout<<endl;
	// for(int i = 0; i < adjList.size(); i++){
	// 	cout<<"P: "<<adjList[i].p.x<<adjList[i].p.y<<" A: ";
	// 	for(int j = 0; j < adjList[i].plist.size(); j++){
	// 		cout<<adjList[i].plist[j].x<<adjList[i].plist[j].y<<" ";
	// 	}
	// 	cout<<endl;
	// }
	// cout<<endl;
	// for(int i = 0; i <= N;i++){
	// 	for(int j = 0; j <= N; j++){
	// 		cout<<maze[i][j]<<' ';
	// 	}
	// 	cout<<endl;
	// }

	//now that I have an adjacency list as a graph representation
	//I can begin to implement Dijkstra's algorithm
	//for now, I'm using the adjList vector even though it's slower(v^2 vs vlogv) than a min-priority queue
	//for no good reason other than familiarity, and it already took longer than v^2 time(N^2) to create the adjList
	while(!(adjList.empty())){
		//for now, using adjList as Q, get min distance in Q
		node* min = &adjList[0];
		int index = 0;
		//mad theta v operation right here
		//if I used a min queue, here's where the improvement would be
		for (int i = 1; i < adjList.size();i++){
			if(*(adjList[i].p.distance) < *(min->p.distance)){
				min = &adjList[i];
				index = i;
			}
		}
		//cout<<"MinQ: "<<min->p.x<<min->p.y<<endl;

		//for neighbors of min, if their distances are smaller, change them
		for(int j = 0; j < min->plist.size();j++){
			//if min's distance is smaller than neighbor's distance
			if(*(min->p.distance) < *(min->plist[j].distance)){
				//change value pointed to by neighbor's distance to value pointed to by min's distance + 1
				*(min->plist[j].distance) = *(min->p.distance) + 1;
			}
		}
		//take min out of adjList
		adjList.erase(adjList.begin() + index);
		//I could build in the case where if bottom left corner is min break
		//but it wouldn't affect the asymptotic runtime of the algorithm
		//it would still be theta(v^2)
		//practically though, it would run a tad bit faster in cases with disconnected segments
	}

	if(maze[N][N] == (N+1)*(N+1) + 1){
		return 0;
	}
	return maze[N][N];
}

int main(){
	cout<<(shortestPath("maze.txt"))+1<<endl;
}
