//
//  Pawn.h
//  chess
//
//  Created by User on 2015-11-25.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#ifndef __chess__Pawn__
#define __chess__Pawn__

#include "Piece.h"
#include "King.h"

//
//  Pawn.cc
//  chess
//
//  Created by User on 2015-11-25.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#include "Pawn.h"

class Pawn : public Piece{
public:
    Pawn(char);
    ~Pawn();
    void calibrate();
    virtual std::string unicode() const;
    double getMaterialValue() const;
};

#endif /* defined(__chess__Pawn__) */
