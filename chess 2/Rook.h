//
//  Rook.h
//  chess
//
//  Created by User on 2015-11-25.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#ifndef __chess__Rook__
#define __chess__Rook__

#include "Piece.h"
#import "King.h"

class Rook : public Piece{
private:
    
public:
    Rook(char);
   // std::string& getType() const;
    virtual double getMaterialValue() const;
    virtual void calibrate();
};


#endif /* defined(__chess__Rook__) */
