//
//  vector.cc
//  a4q1
//
//  Created by User on 2015-11-07.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#include "vector.h"
#include <iostream>

Vector::Vector(){
    list = new int[1];
    length = 0;
    capacity = 1;
}

Vector::~Vector(){
    delete [] list;
}

T Vector::at(int index) const{
    if(index >= length || index < 0)
        return -1;
    
    return list[index];
}

int Vector::find(T num) const{
    for(int i = 0; i < length; i++){
        if(list[i] == num)
            return i;
    }
    return -1;
}

T Vector::first() const{
    return list[0];
}

T Vector::last() const{
    return list[length-1];
}

int Vector::size() const{
    return length;
}

void Vector::doubleCapacity(){
    capacity *= 2;
    T* newList = new T[capacity];
    for(int i = 0; i < length; i++){
        newList[i] = list[i];
    }
    delete [] list;
    list = newList;
}

bool Vector::atCapacity() const{
    return length == capacity;
}



void Vector::add(T num){
    if(atCapacity())
        doubleCapacity();
    list[length++] = num;
}

void Vector::shiftListDownAt(int i){
    for(int j = i + 1; j < length; j++){
        list[j-1] = list[j];
    }
}

bool Vector::remove(T num){
    int i = 0;
    for(; i < length; i++){
        if(list[i] == num){
            shiftListDownAt(i);
            length--;
            return true;
        }
    }
    return false;
}

void Vector::print() const{
    if(list)
    std::cout << "[";
    for(int i = 0; i < length; i++){
        std::cout << list[i] << (i < length - 1 ? ", " : "");
    }
    std::cout << "]\n";
}

