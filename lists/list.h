//
//  list.h
//  a4q1
//
//  Created by User on 2015-11-07.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#ifndef a4q1_list_h
#define a4q1_list_h

template <typename T> class List{

protected:
    int length;
    
public:
    //Creation of Default, ctor, dtor.
    virtual ~List(){}
    virtual void add(T t) = 0;
    virtual T at(int index) const = 0;
    virtual int find(int num) const = 0;
    virtual T first() const = 0;
    virtual T last() const = 0;
    virtual void print() const = 0;
    virtual bool remove(T num) = 0;
    virtual int size() const = 0;
    
    
    
};

#endif
