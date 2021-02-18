
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
	ifstream BigData("TinyData.txt"); 
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
class Node{
	public:
		Node();
		~Node();
		void setContent(char c) { content = c; }
    		Node* findChild(char c);
    		void addChild(Node* child) { children.push_back(child); }
    		void setEnd() { isEnd = true; }
    		bool checkEnd() { return isEnd; }

	private:
		char content;
		bool isEnd;
		vector<Node*> children;
};



//Trie class to be implemented in fourB()
class Trie {
public:
	Trie();
	~Trie();
	void addWord(string s);
	bool searchWord(string s);
	void deleteWord(string s);
private:
	Node* root;
};


Node::Node(){

}
//Find Child method for fourB()
Node* Node::findChild(char c)
	{
		for (int i = 0; i < children.size(); i++)
		{
			Node* ptr = children[i];
			if (ptr->content == c)
			{
				return ptr;
			}
		}
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
	Node* currNode = root;
	if(s.length() == 0){
		currNode->setEnd();
		return;
	}
	for ( int i = 0; i < s.length(); i++ ){        
        	Node* newNode = currNode->findChild(s[i]);
        	if (i == s.length()-1){
            		currNode->setEnd();
        	}
        	if(newNode != NULL){
            		currNode = newNode;
        	}
        	else{
            		Node* tmp = new Node();
            		tmp->setContent(s[i]);
            		currNode->addChild(tmp);
            		currNode = tmp;
    		}
	}
}

//SearchWord method
bool Trie::searchWord(string s){
	Node* currNode = root;
	while(currNode != NULL){
		for(int i = 0; i <s.length(); i++){
			Node* tmp = currNode->findChild(s[i]);
			if(tmp == NULL){
				return 1;
			}
			currNode = tmp;
		}
		if(currNode->checkEnd()){
			return true;
		}
		else{
			return false;
		}
	}
	if(currNode == NULL){
		return false;
	}
	
	
}

int countWords(string s, Trie dictionary)
{
	string substring;
	int count = 0; 

	for (int i = 1; i < s.length(); i++)
	{
		for (int j = 0; j < s.length()- i +1 ; j++)
		{
			substring = s.substr(j,i);

			if ((substring[0]!= 'j') && (substring[0]!= 'J'))
			{
				count += dictionary.searchWord(substring);
			}

		}
	}

	return count;

}

void fourB(){
	int count = 0;
	ifstream data("TinyData.txt");
	ifstream dict("dictionary.txt");

	string myWord;
	
	Trie dictionary;

	if(dict.is_open()){
		while(getline(dict,myWord)){
			dictionary.addWord(myWord);
			
		}
	dict.close();
	}

	string newWord;	

	while(data >> newWord){
		count += countWords(newWord,dictionary);
	}

	cout<<count<<endl;
}


void fourA(){
	char c;
	int totalDigits = 0;
	int BUIDcount = 0;
	bool done = false;
	ifstream myFile;
	myFile.open("TinyData.txt");
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
	//fourA();
	fourB();
	//fourC();
}
