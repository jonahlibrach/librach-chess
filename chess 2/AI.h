//
//  AI.h
//  chess
//
//  Created by User on 2015-11-23.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#ifndef __chess__AI__
#define __chess__AI__

#include "Player.h"
#include <vector>
class AI : public Player{
private:
 
    
    
    int level;
    Move* levelOne(set<Move*>* moves) const;
    Move* levelTwo(Board*, set<Move*>*) const;
    Move* levelThree(Board*, set<Move*>*) const;
    Move* levelFour(Board*, set<Move*>*) const;
    Move* canMovePiece(string, Square*) const;
    bool lessThan(Move*, Move*, Board*) const;
    bool isDiagCheck(Board*, Square*, Piece* king) const;
    bool isVertCheck(Board*, Square*, Piece* king) const;
    bool isKnightCheck(Board*, Square*, Piece*) const;
public:
    AI(int, int);
    ~AI();
    Move* makeMove(Board*, set<Move*>*);

};
#endif /* defined(__chess__AI__) */
