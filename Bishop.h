//
//  Bishop.h
//  chess
//
//  Created by User on 2015-11-25.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#ifndef __chess__Bishop__
#define __chess__Bishop__

#include "Piece.h"
#import "King.h"

class Bishop : public Piece{
private:
    
public:
    Bishop(char);
    virtual double getMaterialValue() const;
    virtual void calibrate();
    std::string unicode() const;
};


#endif /* defined(__chess__Bishop__) */
