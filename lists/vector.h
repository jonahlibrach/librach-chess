//
//  vector.h
//  a4q1
//
//  Created by User on 2015-11-07.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//
#include "list.h"
#ifndef __a4q1__vector__
#define __a4q1__vector__

class Vector : public List{

private:
    T* list;
    int capacity;
    void doubleCapacity();
    bool atCapacity() const;
    void shiftListDownAt(int i);
    
public:
    Vector();
    ~Vector();
    void add(T t);
    T at(int index) const;
    int find(T t) const;
    T first() const;
    T last() const;
    bool remove(T t);
    int size() const;
    void print() const;
    
};

#endif /* defined(__a4q1__vector__) */
