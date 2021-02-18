#include <string>
#include <fstream>
#include <iostream>
#include <ctype.h>
#include <vector>


using namespace std;

//This code is adpated from the Manacher Algorithm
//which can find the length of the largest palindrome substring with O(n)
//https://www.fatalerrors.org/a/longest-palindromic-substring.html
//PreProcess
string preProcess(string s){
	int n = s.length();
	if(n == 0){
		return " ";
	}
	string ret = "^";
	for(int i = 0; i < n; i++){
		ret += "#" + s.substr(i,1);
	}
	ret += "#$";
	return ret;
}

//This method is also adapted from the Manacher algorithm used above
//https://www.fatalerrors.org/a/longest-palindromic-substring.html
//longestPalindrome method to be used in fourC()
string longestPalindrome(string s){
	string T = preProcess(s);
	int n = T.length();
	int *P = new int[n];
	int C = 0, R = 0;
	for(int i = 1; i < n-1; i++){
		int i_mirror = 2*C-i;
		P[i] = (R > i) ? min(R-i, P[i_mirror]) : 0;
		//exapnd the palindrome centered around 'i'
		while(T[i + 1 + P[i]] == T[i - 1 - P[i]]){
			P[i]++;
		}
		if(i + P[i] > R){ //if the plaindrome is centered at i, expand it past R
			C = i;    //then adjust the center based on the expanded palindrome
			R = i + P[i];			
		}
	}
	//find the maximum element in P
	int maxLen = 0;
	int centerIndex = 0;
	for(int i = 1; i < n-1; i++){
		if(P[i] > maxLen){
			maxLen = P[i];
			centerIndex = i;
		}
	}
	delete[] P;

	return s.substr((centerIndex - 1 - maxLen)/2, maxLen);	
}

int fourC(){
	string line;
	ifstream BigData("BigData.txt"); 
	string answer = "";
	while(!BigData.eof()){			//while not at end of file  
		getline(BigData,line);		//get line of BigData
		int string_length = line.length();
		string temp = longestPalindrome(line); //call longestPalindrome and store in temp
		if(temp.length() > answer.length()){   //assign answer the longest plaindrome. 
			answer = temp;
		}
	}
	cout<<answer<<endl;
}
// The code used to construct the trie data structure was taken from a website
// http://www.sourcetricks.com/2011/06/c-tries.html#.VvyRi7wX6hc
//Node Class to be implemented in fourB()
class Node {
public:
    Node() { mContent = ' '; mMarker = false; }
    ~Node() {}
    char content() { return mContent; }
    void setContent(char c) { mContent = c; }
    bool wordMarker() { return mMarker; }
    void setWordMarker() { mMarker = true; }
    Node* findChild(char c);
    void appendChild(Node* child) { mChildren.push_back(child); }
    vector<Node*> children() { return mChildren; }

private:
    char mContent;
    bool mMarker;
    vector<Node*> mChildren;
};

//Trie class to be implemented in fourB()
class Trie {
public:
	Trie();
	~Trie();
	void addWord(string s);
	int searchWord(string s);
	void deleteWord(string s);
private:
	Node* root;
};

//Find Child method for fourB()
Node* Node::findChild(char c){
	for(int i = 0; i < mChildren.size(); i++){
		Node* tmp = mChildren.at(i);
		if(tmp->content() == c){
			return tmp;
		}
	}
	return NULL;
	
}


//Trie Constructor
Trie::Trie(){
	root = new Node();
}

Trie::~Trie(){
	//Free memory
}

//AddWord method
void Trie::addWord(string s){
	Node* current = root;
	if(s.length() == 0){
		current->setWordMarker();
		return;
	}
	for ( int i = 0; i < s.length(); i++ ){        
        	Node* child = current->findChild(s[i]);
        	if ( child != NULL ){
            		current = child;
        	}
        	else{
            		Node* tmp = new Node();
            		tmp->setContent(s[i]);
            		current->appendChild(tmp);
            		current = tmp;
        	}
        	if ( i == s.length() - 1 ){
            		current->setWordMarker();
    		}
	}
}

//SearchWord method
int Trie::searchWord(string s){
	Node* current = root;
	while(current != NULL){
		for(int i = 0; i <s.length(); i++){
			Node* tmp = current->findChild(s[i]);
			if(tmp == NULL){
				return 1;
			}
			current = tmp;
		}
		if(current->wordMarker()){
			return 2;
		}
		else{
			return 0;
		}
	}
	return 1;
	
}



void fourB(){
	
	Trie* trie = new Trie();
	string line = "";
	ifstream dictionary("dictionary.txt");
	while(!dictionary.eof()){
		getline(dictionary, line);
		trie->addWord(line); //create a trie with all the words in dictionary
	}
	dictionary.close();

	int counter = 0;
	int counter2 = 0;
	ifstream BigData("BigData.txt");
	
	while (!BigData.eof()){	//while not at eof
		getline(BigData, line); //get each line from the file
		for(int i = 0; i < line.length(); i++){
			for(int j = 1; j < line.length() - i + 1; j++){
				string testing = line.substr(i,j);
				int number = trie->searchWord(testing); //create substrings of each word in bigData and search for them in the trie
				if(number == 2){
					counter++; //disregard this counter was for total
					if((testing[0] != 'j') && (testing[0] != 'J')){ //disregard all words starting with j or J
						counter2++; //if it finds the word increase the counter
					}
				}
				else if(number == 1){
					break;
				}
			}
		}
	}

	//cout<<"Number of Words: "<<counter<<endl;
	cout<<counter2<<endl;
	delete trie; 
}


void fourA(){
	char c;
	int totalDigits = 0;
	int BUIDcount = 0;
	bool done = false;
	ifstream myFile;
	myFile.open("BigData.txt");
	int i = 0;

	while(!myFile.eof()){				//while not at end of file
		myFile.get(c); 				//gets each charcacter
		if(c == 'U'){				//is the character are U?
			while( i < 8 && !done)		//are the next 8 characters ints?
			{
				myFile.get(c);
				if(isdigit(c)){		//check if the character is a digit
					totalDigits += c - '0'; //add the digits together to check conditional 
					i++;
				}
				else if(c == 'U'){	//if character is U, loop to the top
					i = 0;
					totalDigits = 0;
				}
				else{
					done = true;	//move on
				}
			}
			if((i == 8) && ((totalDigits >= 31) && (totalDigits <= 68))){ //check if the digits sum between 31 and 68
				myFile.get(c); 
				{
					if(!isdigit(c)){ //check if next character is a non digit
						BUIDcount++;//met all requirements, increment BUIDcount
					}
					
				}
			}
			totalDigits = 0; //reset sum of the 8 digits
			i = 0;
			done = false;
		}		
	}
	cout<<BUIDcount<<endl;

}



int main(){
	fourA();
	fourB();
	fourC();
}
