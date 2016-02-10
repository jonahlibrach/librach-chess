//
//  King.h
//  chess
//
//  Created by User on 2015-11-25.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#ifndef __chess__King__
#define __chess__King__

#import "Piece.h"
#include "Chess.h"

class King : public Piece{
    
private:
    bool inLine(Square*, Square*, Square*) const;
public:
    King(char);
    virtual double getMaterialValue() const;
    virtual void calibrate();
    bool requestPermission(Square*, Square*);
    std::string unicode() const;
};

#endif /* defined(__chess__King__) */
