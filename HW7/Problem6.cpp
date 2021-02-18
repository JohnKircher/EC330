#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <string.h>
#include <stdio.h>
#include <queue>
#include <utility>
int n = 0; //n = size of the maze

using namespace std;

struct pointDist{
	pair<int,int> position;
	int dist;
};

void getn(string filename){
	ifstream getSize(filename);
	string line = "";
	int count = 0;

	while(getline(getSize,line)){
		if(count == 0){
			n = line.length() - 1;
		}
		count++;
	}
	getSize.close();
}

void print(int** mazeArr){
	cout<<endl;
	for (int i = 0 ; i < n; i++){
		for (int j = 0 ; j < n; j++){
            		cout << mazeArr[j][i];
        	} 
		cout << endl;
    	}
}

int** readFile(string filename){
	int col = 0;
	int **mazeArr = new int *[n];

	for(int i = 0; i < n; i++){
		mazeArr[i] = new int[n];
	}

	ifstream input(filename);
	string newline = "";

	while (getline(input, newline)){
		for(int row = 0; row < n; row++){
			if(newline[row] != ' '){
				mazeArr[row][col] = stoi(string(1, newline[row]));
			}
		}
		col++;
	}
	return mazeArr;
}

void findPath(int** mazeArr){
	bool found = false;
    	int distance = 0;
    	pointDist position;
    	pointDist tempPos;
    	queue<pointDist> bfsQueue;

	position.position.first = 0;
	position.position.second = 0;
	position.dist = 0;
    	bfsQueue.push(position);

	bool isVisited[n][n];
	memset(isVisited, false, sizeof isVisited);
	isVisited[position.position.first][position.position.second] = true;

	while (!bfsQueue.empty()) {
		position = bfsQueue.front();
		if (position.position.first == n-1 && position.position.second == n-1){
			cout << position.dist << endl;
            		found = true;
            		break;
		}
		bfsQueue.pop();

		for(int i = 0; i < 4; i++){
			if(i == 0){
				tempPos.position.first = position.position.first;
               	 		tempPos.position.second = position.position.second+1;
                		tempPos.dist = position.dist+1;
				
				if (isVisited[tempPos.position.first][tempPos.position.second] == false  && tempPos.position.second <= n - 1){
					if (mazeArr[tempPos.position.first][tempPos.position.second] == 1){
						bfsQueue.push(tempPos);
                        			isVisited[tempPos.position.first][tempPos.position.second] = true;
					}
				}
			}
			else if(i == 1){
				tempPos.position.first = position.position.first;
                		tempPos.position.second = position.position.second-1;
                		tempPos.dist = position.dist+1;

				if (isVisited[tempPos.position.first][tempPos.position.second] == false && tempPos.position.second >= 0){
					if (mazeArr[tempPos.position.first][tempPos.position.second] == 1){
						bfsQueue.push(tempPos);
                        			isVisited[tempPos.position.first][tempPos.position.second] = true;
					}
				}
			}
			else if(i == 2){
				tempPos.position.first = position.position.first-1;
                		tempPos.position.second = position.position.second;
                		tempPos.dist = position.dist+1;
				
				if (isVisited[tempPos.position.first][tempPos.position.second] == false && tempPos.position.first >= 0){
					if (mazeArr[tempPos.position.first][tempPos.position.second] == 1){
						bfsQueue.push(tempPos);
                        			isVisited[tempPos.position.first][tempPos.position.second] = true;		
					}
				}
			}
			else{
				tempPos.position.first = position.position.first+1;
                		tempPos.position.second = position.position.second;
               	 		tempPos.dist = position.dist+1;

				if (isVisited[tempPos.position.first][tempPos.position.second] == false && tempPos.position.first <= n - 1){
					if (mazeArr[tempPos.position.first][tempPos.position.second] == 1){
						bfsQueue.push(tempPos);
                        			isVisited[tempPos.position.first][tempPos.position.second] = true;
					}
				}	
			}
		}
	}
	if(found == false) {cout<< "0\n";}
}

int main(int argc, char** argv){
	string filename = argv[1];

	getn(filename);

	int** mazeArr;
	mazeArr = readFile(filename);

	findPath(mazeArr);

	return 0;
}
