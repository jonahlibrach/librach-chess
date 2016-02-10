//
//  unosrtedlist.h
//  a4q1
//
//  Created by User on 2015-11-07.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#ifndef __a4q1__unosrtedlist__
#define __a4q1__unosrtedlist__

#include "list.h"
#include <iostream>


template <typename T>

class UnsortedList : public List<T>{
    
protected:
   struct Node{
        Node(T& val);
        ~Node();
        Node* next;
        T& val;
    };
    Node* head;

private:
    Node* lastNode() const;

public:
    UnsortedList<T>();
    virtual ~UnsortedList();
    virtual void add(T t);
    virtual T at(int index) const;
    virtual int find(T t) const;
    virtual T first() const;
    virtual T last() const;
    virtual void print() const;
    virtual bool remove(T num);
    virtual int size() const;
    
};



#endif /* defined(__a4q1__unosrtedlist__) */
