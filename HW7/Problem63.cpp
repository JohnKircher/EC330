#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main(){
  ifstream mazein("maze.txt");
  string line;
  int N;

  if (mazein){
    getline(mazein,line);
    N = line.length();
  }
  else{
    cout << "file was not opened" << endl;
  }
  mazein.close();

  int maze[N][N];
  int i=0;
 
  mazein.open("maze.txt");
  while (getline(mazein,line)){
    for (int j=0; j<N; j++){
      maze[i][j]=line[j]-'0';
    } 
    i++;
  }
  mazein.close();
  if (maze[0][0]!=1){
    cout << "Invalid maze because maze(0,0) is 0" << endl;
    return 0;
  }

  int process[N][N];
  int predx[N][N];
  int predy[N][N];
  for (int c=0; c<N; c++){
    for (int k=0; k<N; k++){
      process[c][k]=0;
      predx[c][k]=N+10;
      predy[c][k]=N+10;
    }
  }
  process[0][0]=1;
  predx[0][0]=-1;
  predy[0][0]=-1;
  vector<vector<int> > rs;
  vector<vector<int> > ds;
  vector<int> firstr;
  vector<int> firstd;
  rs.push_back(firstr);
  ds.push_back(firstd);
  int done=0;
  int steps = 0;
  int r,d;
  rs[0].push_back(0);
  ds[0].push_back(0);
  while (done==0){
    //cout << " here while------------------------------------------------- " << endl;
    vector<int> localr,locald;
    rs.push_back(localr);
    ds.push_back(locald);
    int localc = 0;
    if (rs[steps].size()==0){
      cout << "0" << endl;
      return 0;
    }
    for (int c=0; c<rs[steps].size(); c++){
      //      cout << " here for "<< rs[steps][c]+1 << " " << ds[steps][c]+1 << endl;
      if (process[steps][localc] == 2){
	cout << "break" << endl;
	break;
      }
      r = rs[steps][localc];
      d = ds[steps][localc];
      if (r<N){
	if (process[r+1][d] == 0){
	  if (maze[r+1][d] == 1){
	    // cout << "to" << r+2 << d+1 << N << endl;
	    if (r+1==N-1 && d==N-1){
	      done = 1; //remember to steps++
	      break;
	    }
	    process[r+1][d] = 1;
	    rs[steps+1].push_back(r+1);
	    ds[steps+1].push_back(d);
	    predx[r+1][d]=r;
	    predy[r+1][d]=d;
	  }
	}
      }
      if (r>0){
	if (process[r-1][d] == 0){
	  if (maze[r-1][d] == 1){
	    //cout << "to" << r << d+1 << endl;
	    process[r-1][d] = 1;
	    rs[steps+1].push_back(r-1);
	    ds[steps+1].push_back(d);
	    predx[r-1][d]=r;
	    predy[r-1][d]=d;	    
	  }
	}
      }
      if (d<N){
	if (process[r][d+1] == 0){
	  if (maze[r][d+1] == 1){
	    //cout << "to" << r+1 << d+2 << endl;
	    if (r==N-1 && d+1==N-1){
	      done = 1; // same!!!!!!!!!!!!!!!!!!!!!
	      break;
	    }
	    process[r][d+1] = 1;
	    rs[steps+1].push_back(r);
	    ds[steps+1].push_back(d+1);
	    predx[r][d+1]=r;
	    predy[r][d+1]=d;
	  }
	}
      }
      if (d>0){
	if (process[r][d-1] == 0){
	  if (maze[r][d-1] == 1){
	    //cout << "to" << r+1 << d << endl;
	    process[r][d-1] = 1;
	    rs[steps+1].push_back(r);
	    ds[steps+1].push_back(d-1);
	    predx[r][d-1]=r;
	    predy[r][d-1]=d;
	  }
	}
      }
      localc++;
      process[r][d]=2;
    }
    steps++;
  }
 
  cout << steps << endl;
  return 0;
}