//
//  LinkedList.h
//
//  Copyright © Tali Moreshet. All rights reserved.
//

#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>

using namespace std;

template <class T = int>
class Node {
public:
    Node();                                         // default constructor
    Node(const T& data, Node<T>* next = nullptr);   // donstructor
    T data;                                         // node data
    Node<T>* next;                                  // node next pointer
};

template <class T = int>
class LinkedList {
public:
    LinkedList();                                   // constructor
    ~LinkedList();                                  // destructor
    T deleteFromHead();                             // removes and returns content of head
    T deleteFromTail();                              // removes and returns content of tail
    void deleteNode(T data);                         // removes node with specified data
    void InsertToHead(T data);                      // insert node with data at the head
    void InsertToTail(T data);                      // insert node with data at the tail
    int getSize();                                  // returns size of linked list
    void print();                                   // prints linked list
private:
    Node<T>* head;                                  // head of linked list
};

template <class T = int>
class StackFromList{
	private:
		LinkedList<T> stackList;
	public:
		StackFromList();
		~StackFromList();
		T pop();
		void push(T x);
		bool isEmpty();
};

template <class T = int>
class QueueFromList{
	private:
		LinkedList<T> queueList;
	public:
		QueueFromList();
		~QueueFromList();
		void enqueue(T x);
		T dequeue();
		bool isEmpty();
};
/******* From here down is the content of the LinkedList.cpp file: ***********************/

 /* Implementation of Node */

 // default constructor
 template<class T>
 Node<T>::Node()
 {
 }

 
 
 // constructor
 template<class T>
 Node<T>::Node(const T& data, Node<T>* next)
 {
     this->data = data;
     this->next = next;
 }
 
 /* Implementation of linked list */

 // constructor
 template <class T>
 LinkedList<T>::LinkedList()
 {
     head = nullptr;
 }

 // destructor
 template <class T>
 LinkedList<T>::~LinkedList()
 {
 	Node<T>* curr = head;
 	while(curr != 0){
		Node<T>* next = curr->next;
		delete(curr);
		curr = next;
	}
	head = nullptr;
 }

 template <class T>
 T LinkedList<T>::deleteFromHead()
 {
 	T data;
	if(head != nullptr){
		if(head->next == nullptr){
			data = head->data;
			delete(head);
			head = nullptr;
			return data;			
		}
		else{
			Node<T>*temp = head;
			data = temp->data;
			head = head->next;
		}
	}
	return data;
 }


 template <class T>
 T LinkedList<T>::deleteFromTail()
 {
 	if(head == nullptr){
		return 0;
	}
	if(head->next == nullptr){
		T data = head->data;
		delete(head);
		head = nullptr;
		return data;
	}
	Node<T>*temp = head;
	while(temp->next->next != nullptr){
		temp = temp->next;
	}
	T data = temp->next->data;

	delete(temp->next);
	temp->next = nullptr;
	return data;
 }
 

 template <class T>
 void LinkedList<T>::deleteNode(T data)
 {
 	Node<T> *temp = this->head;
	if(temp->data == data){
		head = temp->next;
		delete(temp);
	}
	else{
		while(temp->next->data != data){
			temp = temp->next;
		}
	Node<T> *nodeToDelete = temp->next;
	if((temp->next->next) == nullptr){
		temp->next = nullptr;
		delete(nodeToDelete);		
	}
	else{
		temp->next = temp->next->next;
		delete(nodeToDelete);
	}
	}
	
 }
 

 template <class T>
 void LinkedList<T>::InsertToHead(T data)
 {
     Node<T> * newNode = new Node<T>(data, nullptr);
     
     if (head == nullptr)
         head = newNode;
     else
     {
         newNode->next = head;
         head = newNode;
     }
 }


 template <class T>
 void LinkedList<T>::InsertToTail(T data)
 {
	Node<T>* newNode = new Node<T>(data,nullptr);
	if(head == nullptr){
		head = newNode;
	}
	else{
		Node<T>* temp = head;
		while(temp->next != nullptr){
			temp = temp->next;
		}
	temp->next = newNode;
	}
 }


 template <class T>
 int LinkedList<T>::getSize()
 {
 	int size = 0;
	Node<T>* temp = head;
	while(temp != nullptr){
		size++;
		temp = temp->next;
	}
	return size;
 }


 template <class T>
 void LinkedList<T>::print()
 {
     if (head == nullptr)
     {
         cout << "Linked list is empty" << endl;;
         return;
     }
     
     cout << head->data << " ";
     
     if (head->next == nullptr)
     {
         cout << endl;
         return;
     }
 
     Node<T>* currNode = head->next;
     Node<T>* prevNode = head;
 
     
     while (currNode->next != nullptr)
     {
         cout << currNode->data << " ";
         prevNode = currNode;
         currNode = currNode->next;
     }
 
     cout << currNode->data << endl;
     return;
 }

//Stack Constructor
 template<typename T>
 StackFromList<T>::StackFromList(){		
 }

//Stack Deconstructor
 template<typename T>
 StackFromList<T>::~StackFromList(){
 	while(!isEmpty()){
		pop();
	}
 }
//Stack pop function
 template<typename T>
 T StackFromList<T>::pop(){
 	if(isEmpty()){
		cout<<"Error, stack is empty"<<endl;
		return 0;
	}
	T x = stackList.deleteFromTail();
	return x;
 }

//Stack push function
 template<typename T>
 void StackFromList<T>::push(T x){
	stackList.InsertToTail(x);
 }

//Stack bool isEmpty Function   
 template<typename T>
 bool StackFromList<T>::isEmpty(){
 	if(stackList.getSize() == 0){
		return true;
	}
	else{
		return false;
	}
 }

//constructor for Queue
 template<typename T>
 QueueFromList<T>::QueueFromList(){
 }

//destrcutor for Queue
 template<typename T>
 QueueFromList<T>::~QueueFromList(){
 	while(!isEmpty()){
		dequeue();	
 	}	
 }

//Enqueue function
 template<typename T>
 void QueueFromList<T>::enqueue(T x){
 	queueList.InsertToTail(x);
 }

//Dequeue function
 template<typename T>
 T QueueFromList<T>::dequeue(){
 	if(isEmpty()){
		cout<<"Error, Queue is empty"<<endl;
		return 0;
	}
	T x = queueList.deleteFromHead();
	return x;
 }


//Queue bool isEmpty Function
 template<typename T>
 bool QueueFromList<T>::isEmpty(){
 	if(queueList.getSize() == 0){
		return true;
	}
	else{
		return false;
	}
 }  


   
#endif /* LinkedList_h */
