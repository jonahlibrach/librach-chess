//
//  Move.cc
//  chess
//
//  Created by User on 2015-11-23.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#include "Move.h"

Square* Move::from() const{
    return initial;
}
Square* Move::to() const{
    return final;
}