//
//  LSorter.cpp
//  LSorter
//
//  Created by Tali Moreshet
//  Copyright ©  Tali Moreshet. All rights reserved.
//

#include <algorithm>
#include "LSorter.h"

using namespace std;
//merge function
void LSorter::merge(LNode** start1, LNode** end1, LNode** start2, LNode** end2){
	LNode* temp = nullptr;
	if((*start1)->val > (*start2)->val){ //compare the values of start1 and start2. We need to make sure that the first node
		swap(*start1, *start2);      //of the second list is higher. Otherwise, we need to swap the pointers. 
		swap(*end1, *end2);
	}
	
	//merge remaining nodes
	LNode* firstStart = *start1;
	LNode* firstEnd = *end1;
	LNode* secondStart = *start2;
 	LNode* secondEnd = *end2;
	LNode* secondEndNext = (*end2)->next;
	while((firstStart != firstEnd) && (secondStart != secondEndNext)){ 
		if(firstStart->next->val > secondStart->val){ //compare the next value of firstStart and the current value of secondStart.
			temp = secondStart->next;             // if secondStart is smalled than the next value of firstStart, then we need
			secondStart->next = firstStart->next; // to insert start2 after start1. Continue to do this until we reach the end
			firstStart->next = secondStart;       // of start1 or start2.
			secondStart = temp;
		}
		firstStart = firstStart->next; //look at the next node
	}
	if(firstStart == firstEnd){
		firstStart->next = secondStart; //if start1 ends we need to set its next to start2 because depending on size there
	}					//there may be elements left out which could be greater than the last value of start1
	else{
		*end2 = *end1; //otherwise when start2 ends we assign end2 to end1 because we need to be able to determine the start1 for 
	}		       //the next sort. 			
}

//sortList function, adopteed from geeksforgeeks.org's void mergeSort() function.
LNode* LSorter::sortList(LNode* head){
	if(head == nullptr){ //if linked list is empty we return head
		return head;	
	}
	LNode* start1 = nullptr;
 	LNode* end1 = nullptr;
	LNode* start2 = nullptr;
 	LNode* end2 = nullptr;
	LNode* previousend = nullptr;
	int len = 0;
	LNode* iterate = head;
	while(iterate != nullptr){ //this loop finds the length of the linked list to be used in the for loop. 
		len++;
		iterate = iterate->next;	
	}

	for(int gap = 1; gap < len; gap = gap*2){ //merge sort first merges two items, then 4, etc. So we use an integer 'gap'
		start1 = head;			  //to store the gap so we can find the midpoint around where the linked list needs to be sorted. 
		
		while(start1){
			bool isFirstIteration = 0;
			if(start1 == head){
				isFirstIteration = 1;
			}
		//Merging for the first linked list
		int counter = gap;
		end1 = start1;
		
		while(--counter && end1->next){
			end1 = end1->next;
		}
		//Merging for the second linked list
		start2 = end1->next;
		if(!start2){
			break;
		}
		
		counter = gap;
		end2 = start2;
		
		while(--counter && end2->next){
			end2 = end2->next;
		}
		//storing the next iteration
		LNode* temp = end2->next;
		//merging (start1,end1) and (start2, end2) together
		merge(&start1, &end1, &start2, &end2);
		//Update the head for the first Iteration
		if(isFirstIteration){
			head = start1;
		}
		//Otherwise, append the previous list
		else{
			previousend->next = start1;
		}
		
		previousend = end2;
		start1 = temp;
		}
		
		previousend->next = start1;
	}
	return head;	
    
}

