//John Kircher
#include "MaxProduct.h"
using namespace std;
long MaxProductClass::MaxProduct(string file){
	maxResult = -999999;
	string line;
	ifstream myfile(file.c_str());
  	if (myfile.is_open())
  	{
		while(getline(myfile,line)){
			int j = 0;
			int k = 0;
			result = -999999;
			long arr[100];
			for(int i = 0; i < line.length(); i++){
				if(line[i]==' '){
					arr[k]=stol(line.substr(j,i-j));
					if(k==0||k==99){
						if(arr[k] > result){
							result = arr[k];
						}
					}
					else if(k==1||k==98){
						if(arr[k]*arr[k-1] > result){
							result = arr[k]*arr[k-1];
						}
						if(arr[k] > result){
							result = arr[k];
						}
					}	
					else{
						if(arr[k]*arr[k-1] > result){
							result = arr[k]*arr[k-1];
						}
						if(arr[k]*arr[k-1]*arr[k-2] > result){
							result = arr[k]*arr[k-1]*arr[k-2];
						}
						if(arr[k-1]*arr[k-2] > result){
							result = arr[k-1]*arr[k-2];
						}
						if(arr[k] > result){
							result = arr[k];
						}
					}
					j = i+1;
					k++;
				}
			}
			if(result > maxResult){
				maxResult = result;
			}
			cout << result << '\n';
		
		}	
    		myfile.close();
	}
	else cout << "could not open file";
	return maxResult;
}		
