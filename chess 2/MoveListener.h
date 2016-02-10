//
//  MoveListener.h
//  chess
//
//  Created by User on 2015-11-30.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#ifndef chess_MoveListener_h
#define chess_MoveListener_h
#include "Move.h"
class MoveListener{
    virtual void notifyMove(Move* m) = 0;
};


#endif
