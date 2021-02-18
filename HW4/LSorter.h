//
//  LSorter.h
//  LSorter
//
//  Created by Tali Moreshet
//  Copyright © Tali Moreshet. All rights reserved.
//

#ifndef LSorter_h
#define LSorter_h

#include <stdio.h>
#include "LNode.h"


class LSorter {
public:
    LNode* sortList(LNode* head);
	
    //Merge function that merges the two sorted parts of the linked list. 
    //Adopted from Iterative merge sort for linked list at geeksforgeeks.org
    void merge(LNode** start1, LNode** end1, LNode** start2, LNode** end2); 
};

#endif /* LSorter_h */
