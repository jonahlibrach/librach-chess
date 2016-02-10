//
//  Move.h
//  chess
//
//  Created by User on 2015-11-23.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#ifndef __chess__Move__
#define __chess__Move__

#include <string>
#include "Square.h"
class Square;
class Move{
    std::string move;
    Square* initial, *final;
public:
    Move();
    ~Move(); 
    Square* from() const;
    Square* to() const;
    std::string toString() const;
    double value() const;
};

#endif /* defined(__chess__Move__) */
