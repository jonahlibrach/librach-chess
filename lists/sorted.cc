//
//  sortedlist.cc
//  a4q1
//
//  Created by User on 2015-11-07.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#include "sorted.h"

void SortedList::addFront(T& num){
    
    Node* newHead = new Node(num);
    newHead -> next = head ? head : NULL;
    head = newHead;

}

SortedList::SortedList() : UnsortedList(){}

void SortedList::add(T& num){
    std::cerr << "Sorted: adding " << num << std::endl;
    if(head == NULL){
        addFront(num);
    }
    else if(num <= head -> val){
        std::cerr << "num <= head -> val" << std::endl;
        Node* newHead = new Node(num);
        newHead -> next = head;
        head = newHead;
    }
    else{
        Node* ptr = head;
        while(ptr -> next != NULL && ptr -> next -> val < num){
            ptr = ptr -> next;
        }
        Node* toAdd = new Node(num);
        std::cerr << "Created a node with val: " << toAdd -> val << std::endl;
        std::cerr << "It will come in right after: " << ptr -> val << std::endl;
        toAdd -> next = ptr -> next;
        ptr -> next = toAdd;
    }
    length++;
}


int SortedList::find(int num) const{
    
    if(head == NULL || length == 0)
        return -1;
    int i = 0;
    Node* ptr = head;
    while(ptr != NULL){
        if(ptr -> val == num)
            return i;
        i++;
        ptr = ptr -> next;
    }
    return -1;
    
}

bool SortedList::remove(int num){

    if(length == 0)
        return false;
    if(head -> val == num){
        Node* toDelete = head;
        head = head -> next;
        delete toDelete;
        length--;
        return true;
    }
    Node* ptr = head;
    while(ptr -> next != NULL){
        
        if(ptr -> next -> val == num){
            
            Node* toDelete = ptr -> next;
            ptr -> next = toDelete -> next;
            delete toDelete;
            length--;
            return true;
            
        }
        ptr = ptr -> next;
    }
    
    return false;
}
