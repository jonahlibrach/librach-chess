//
//  Queen.h
//  chess
//
//  Created by User on 2015-11-25.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#ifndef __chess__Queen__
#define __chess__Queen__


//#import "Player.h"
#include "Chess.h"
#import "King.h"
class King;

class Queen : public Piece{
private:
    
public:
    Queen(char);
    virtual double getMaterialValue() const;
    virtual void calibrate();
    std::string& getType() const;
};

#endif /* defined(__chess__Queen__) */
