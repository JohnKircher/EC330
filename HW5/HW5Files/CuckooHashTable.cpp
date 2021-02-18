#include <vector>
#include <iostream>
#include "CuckooHashTable.h"

using namespace std;

//CuckooHashTable Constructor
CuckooHashTable::CuckooHashTable(){
	vector<string> V1 (LOGICAL_SIZE);
	vector<string> V2 (LOGICAL_SIZE);
	contents.push_back(vector<string>(V1));
	contents.push_back(vector<string>(V2));
	
	this->currentSize = 0;	
}

//CuckooHashTable add(string value)
//Searches for an open slot for the value to be inserted,
//if table is empty, add the number. Otherwise sace the collided
// into the temp table. Then calculate new slot and add the collided
// to the correct position. 
void CuckooHashTable::add(string value){
	
	static int which = 0;
	which = 0;

	int rehash = 0;
	string temp;

	while(true){
		//if table is empty, add value to it
		if((contents[which][hashCode(value,which)]).empty() == true){
			contents[which][hashCode(value,which)] = value; //add value
			currentSize++; //increase currentSize
			break;
		}
		
		else{
			temp = contents[which][hashCode(value,which)]; //otherwise, store collided into variable temp
			contents[which][hashCode(value,which)] = value; //add value 

			if(which == 1){ //if collided, send it to table2.
				which = 0;
			}
			else{
				which = 1;
			}
			//add the collided number into table2
			if((contents[which][hashCode(temp,which)]).empty() == true){
				contents[which][hashCode(temp,which)] = temp; //add value
				currentSize++; //increase currentSize
				break;
			}
			else{
				//Detects if there is an infinite loop, since the amount of times
				//we want to rehash cannot be eqaul to currentSize otherwise we can never enter another value  
				if(rehash == currentSize){
					cout << "Error: Insert causes infinite loop\n" << endl;
					exit(EXIT_FAILURE);
				}
				rehash++; //increase rehash since there was a collision. 
			}			
		}
	}

	
}

//CuckooHashTable hashCode
//Determines which slot will be hasing too
//and applies the correct hash formula. 
int CuckooHashTable::hashCode(string value, int which){
	int hash1 = 0;
	int hash2 = 0;
	
	int number = stoi(value);

	if(which == 1){
		hash2 = 11-(number%11);
		return hash2;
	}
	else{
		hash1 = number%13;
		return hash1;
	}
	
}

//CuckooHashTable print
//Loops through each hash table and 
//prints its' values.
void CuckooHashTable::print(){
	cout << "Table 1:" << endl;
	for(int i = 0; i < 13; i++){
		if(contents[0][i].empty() == true){
			cout << "-" << endl;
		}
		else{
			cout << contents[0][i] << endl;
		}
	}
	cout << "\nTable 2:" << endl;
	for(int i = 0; i < 13; i++){
		if(contents[1][i].empty() == true){
			cout << "-" << endl;
		}
		else{
			cout << contents[1][i] << endl;
		}
	}
}


