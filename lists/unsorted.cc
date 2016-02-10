//
//  UnsortedList.cc
//  a4q1
//
//  Created by User on 2015-11-07.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#include "unsorted.h"
#include <iostream>
template <typename T>

UnsortedList<T>::Node::Node(T& val) : next(NULL), val(val){}

template <typename T>
UnsortedList::Node* UnsortedList<T>::lastNode() const{
    if(head == NULL)
        return NULL;
    Node* ptr = head;
    while(ptr -> next != NULL){
        ptr = ptr -> next;
    }
    return ptr;
}

template <typename T>
UnsortedList<T>::Node::~Node(){
    next = NULL;
    val = 0;
}

template <typename T>
UnsortedList<T>::UnsortedList(){
    head = NULL;
    length = 0;
}

template <typename T>
UnsortedList<T>::~UnsortedList(){
    if(head != NULL){
        while(head -> next != NULL){
            Node* ptr = head -> next -> next;
            delete head -> next;
            head -> next = ptr;
        }
    }
    delete head;
}

template <typename T>
void UnsortedList::add(T& num){
    Node* ptr = lastNode();
    Node* toAdd = new Node(num);
    if(ptr == NULL){
        head = toAdd;
    }else{
        ptr -> next = toAdd;
    }
    length++;
}

template <typename T>
int UnsortedList::at(int index) const{
    Node* ptr = head;
    if(index >= length || index < 0)
        return -1;
    for(int i = 0; i < index; i++)
        ptr  = ptr -> next;
    return ptr -> val;
}

template <typename T>
T& UnsortedList::first() const{
    return head -> val;
}

template <typename T>
T& UnsortedList::last() const{
    if(head == NULL)
        return -1;
    return (lastNode() -> val);
    
}

template <typename T>
int UnsortedList::size() const{
    return length;
}

template <typename T>
int UnsortedList::find(T& num) const{
    if(length == 0)
        return false;
    Node* ptr = head;
    for(int i = 0; ptr != NULL; i++){
        if(ptr -> val == num){
            return i;
        }
        ptr = ptr -> next;
    }
    return -1;
}

template <typename T>
bool UnsortedList<T>::remove(T t){
    if(length == 0)
        return false;
    Node* ptr = head;
    if(head -> val == num){
        head = head -> next;
        delete ptr;
        length--;
        return true;
    }
    while(ptr -> next != NULL){
        if(ptr -> next -> val == num){
            Node* toDelete = ptr -> next;
            ptr -> next = ptr -> next -> next;
            delete toDelete;
            length--;
            return true;
        }
        ptr = ptr -> next;
    }
    return false;
}

template <typename T>
void UnsortedList::print() const{
    std::cout << "[";
    Node* ptr = head;
    while(ptr != NULL){
        std::cout << ptr -> val << (ptr -> next ? ", " : "");
        ptr = ptr -> next;
    }
    std::cout << "]" << std::endl;
}

