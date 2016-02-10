//
//  Square.h
//  chess
//
//  Created by User on 2015-11-25.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#ifndef __chess__Square__
#define __chess__Square__



#include <iostream>
#include <sstream>
#include <set>
#include "Chess.h"

class Piece;

class Square{
    
private:
    Piece* p;
    std::set<Square*>* controllers;
    const int row, col;
public:
    Square(int, int);
    ~Square();
    
    double controlValue() const;
    std::set<Square*>* getControllers() const;
    
    void addController(Square*);
    void removeController(Square*);
    
    int getRow() const;
    int getColumn() const;
    
    Piece* piece() const;
    Piece* setPiece(Piece* newPiece);
    void printInfoTo(std::ostream&) const;
    friend std::ostream& operator<<(std::ostream&, const Square&);
    std::ostream& operator<<(std::ostream&) const;
};



#endif /* defined(__chess__Square__) */
