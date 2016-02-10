//
//  Knight.h
//  chess
//
//  Created by User on 2015-11-25.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#ifndef __chess__Knight__
#define __chess__Knight__

#include "Piece.h"
#import "King.h"

class Knight : public Piece{
public:
    Knight(char);
    virtual double getMaterialValue() const;
    virtual void calibrate();
    virtual std::string unicode() const;
};

#endif /* defined(__chess__Knight__) */
