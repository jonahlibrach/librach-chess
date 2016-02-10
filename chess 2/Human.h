//
//  Human.h
//  chess
//
//  Created by User on 2015-11-23.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#ifndef __chess__Human__
#define __chess__Human__

#include "Player.h"
#include <iostream>
class Human : public Player{
    
private:
    std::istream* input;
    bool findMove(Move*, set<Move*>*) const;
    void printHint(set<Move*>*) const;
public:
    Human(int, std::istream&);
    ~Human();
    Move* makeMove(Board* b, std::set<Move*>*);
    
    
};

#endif /* defined(__chess__Human__) */
