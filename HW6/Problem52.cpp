#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
//#include <ctype.h>
#include <sstream>
#include <cctype>

using namespace std;


void fourA() {
    vector<int> id;
    bool nextIsNotNum = false;
    bool foundU = false;
    int sum = 0;
    int count = 0;

    ifstream input("BigData.txt");

    char character;
    while (input.get(character)) {
//        cout << character;
        if (character == 'U' && !foundU) {
            foundU = true;
            continue;
        }
        if (foundU) {
            if (((int) character >= (int) '0') && ((int) character <= (int) '9')) {

                id.push_back(character - 48);
            } else {
                id.clear();
                foundU = false;
                sum = 0;
            }
            if ((id.size() == 8)) {
//                cout << "Next char: " << (char) input.peek() << endl;
                char nextChar = input.peek();

                if (((int) nextChar >= (int) '0') && ((int) nextChar <= (int) '9')) {
                    nextIsNotNum = false;
                } else {
                    nextIsNotNum = true;
                }
                if (nextIsNotNum) {
                    for (int i = 0; i < id.size(); i++) {
//                        cout << id.at(i);
                        sum += id.at(i);
                    }
//                    cout << endl;
                    if ((sum >= 31) && (sum <= 68)) {
                        count++;
                        id.clear();
                        nextIsNotNum = false;
                        foundU = false;
                        sum = 0;
                    }
                } else {
                    id.clear();
                    foundU = false;
                    sum = 0;
                }
            }
        }
    }

    cout << "Total IDs found: " << count << endl;
    input.close();
}


class Node {
public:
    Node() {
        trieContent = ' ';
        isWord = false;
    }

    ~Node() {

    }

    char content() {
        return trieContent;
    }

    void setContent(char c) {
        trieContent = c;
    }

    bool wordMarker() {
        return isWord;
    }

    void setWordMarker() {
        isWord = true;
    }

    Node *findChild(char c);

    void appendChild(Node *child) {
        trieChildren.push_back(child);
    }

    vector<Node *> children() { return trieChildren; }

private:
    char trieContent;
    bool isWord;
    vector<Node *> trieChildren;
};

class Trie {
public:
    Trie();

    ~Trie();

    void addWord(string s);

    int countTotalWords(string s);

    void deleteWord(string s);

private:
    Node *root;
};

Node *Node::findChild(char c) {
    for (int i = 0; i < trieChildren.size(); i++) {
        Node *tmp = trieChildren.at(i);
        if (tmp->content() == c) { return tmp; }
    }
    return NULL;
}

Trie::Trie() { root = new Node(); }

Trie::~Trie() {// Free memory
}

void Trie::addWord(string s) {
    Node *current = root;
    if (s.length() ==
        0) {
        current->setWordMarker(); // an empty word
        return;
    }
    for (int i = 0; i < s.length(); i++) {
        Node *child = current->findChild(s[i]);
        if (child != NULL) { current = child; }
        else {
            Node *tmp = new Node();
            tmp->setContent(s[i]);
            current->appendChild(tmp);
            current = tmp;
        }
        if (i == s.length() - 1)current->setWordMarker();
    }
}

int Trie::countTotalWords(string s) {
    Node *current = root;
    Node *next;
    int count = 0;
    while (current != NULL) {
        for (int i = 0; i < s.length(); i++) {
            Node *tmp = current->findChild(s[i]);

            if (current->wordMarker()){
                count++;
            }
            if (tmp == NULL){
                return count;
            }
            else if ((s.length() == 1) && count > 0){
                return count;
            }

            current = tmp;
        }


    }
//    return count;
}// Test program
void fourB() {
    Trie *trie = new Trie();
    string word;
    ifstream input("dictionary.txt");

    while(getline(input, word)){
#ifndef EXCLUDE
        if((word.at(0) != 'Y') && (word.at(0) != 'y') ){
            trie->addWord(word);
        }
#else
        if(1){
            trie->addWord(word);
        }
#endif
    }
    input.close();
    stringstream buffer;
    string currWord = "";
    bool wordFinished;
    fstream input2("BigData.txt");
    buffer << input2.rdbuf();
    string textfile = buffer.str();
    int i = 0;
    int count = 0;
    int localTotal = 0;

    int totalChars = 604501072;

    while(i < textfile.length()){
#ifdef PROGRESS
        cout << i << " of " << totalChars << endl;
#endif
        int isAlphaChar = isalpha(textfile.at(i));
        switch (isAlphaChar) {
            case 0:
                if(isblank(textfile.at(i))){
                    i++;
                    continue;
                }
                if(!currWord.empty()){
                    wordFinished = true;
                } else {
                    break;
                }
                break;
            case 1:
                currWord+=textfile.at(i);
                i++;
                if(i == textfile.length()){
                    wordFinished = true;
                    break;

                }
                continue;
        }
        if(wordFinished){
            int wordL = currWord.length();
            int wordCount;
#ifdef DEBUG
            cout << currWord << " ";
           cout << "Current Count: ";
#endif
            for(int j = 0; j < wordL; j++){
                wordCount = trie->countTotalWords(currWord);
                localTotal+= wordCount;
#ifdef DEBUG
                cout << wordCount << " ";
#endif
                currWord.erase(0,1);
            }
            count += localTotal;
#ifdef DEBUG
            cout << " Total for word: " << localTotal << endl;
#endif
            localTotal = 0;
        }
        wordFinished = false;
        currWord = "";
        i++;
    }
    cout << "Total word count: " << count << endl;

    delete trie;
    input2.close();
}

void fourC() {
    char c;
    stringstream buffer;
    vector<char> file;
    file.reserve(100000);

    //input all characters into a vector
    ifstream input("BigData.txt");
    buffer << input.rdbuf();
    string textfile = buffer.str();
    int n = textfile.length();

    //return string if length is 2
    if (n == 2) {
        cout << "Longest palindrome: " << textfile << endl;
        return;
    }

    int leftBorder = 0;
    int rightBorder = 0;
    int left, right;
    int maxlength = 0;


    for (int i = 0; i < n; i++) {


        if (i > rightBorder) {

            left = i - 1;
            right = i + 1;
            while ((textfile[left] == textfile[right]) && ((left) >= 0) && ((right) < n)) {
                if ((right - left + 1) > maxlength) {
                    leftBorder = left;
                    rightBorder = right;
                    maxlength = right - left + 1;
                }

                left = left - 1;
                right = right + 1;
            }


            left = i - 1;
            right = i;
            while ((textfile[left] == textfile[right]) && ((left) >= 0) && ((right) < n)) {

                if ((right - left + 1) > maxlength) {
                    leftBorder = left;
                    rightBorder = right;
                    maxlength = right - left + 1;
                }

                left = left - 1;
                right = right + 1;
            }
        }
    }

    textfile = textfile.substr(leftBorder, maxlength);
    cout << "Longest palindrome: " << textfile << endl;
    input.close();
}

int main() {
    fourA();
    fourB();
    fourC();
    return 0;
}
