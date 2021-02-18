#include<iostream>
#include<cstdlib>
using namespace std;

int steps(int n){
	
	if(n == 1 || n == 0){
		return 1;
	}	
	else if(n == 2){
		return 2;
	}	
	else{
		return steps(n -3) + steps(n-2) + steps(n-1);
	}
	

}

int main(int argc, char *argv[]){

	int number = atoi(argv[1]);
	int result = steps(number);
	//cout << "There are " << result << " ways to jump " << number << " steps\n";
	cout << result << "\n";
	return 0;
}
