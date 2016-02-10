//
//  sortedlist.h
//  a4q1
//
//  Created by User on 2015-11-07.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#ifndef __a4q1__sortedlist__
#define __a4q1__sortedlist__

#include "unsorted.h"
template <class T>

class SortedList : public UnsortedList<T>{
private:
    void addFront(T& num);
public:
    SortedList();
    void add(T& t);
    int find(T& t) const;
    bool remove(T& t);
};

#endif /* defined(__a4q1__sortedlist__) */
