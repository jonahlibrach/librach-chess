//
//  Game.h
//  chess
//
//  Created by User on 2015-11-25.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#ifndef __chess__Game__
#define __chess__Game__


#include <iostream>
#include <vector>
#include "Player.h"
#include "Board.h"
#include "Chess.h"
#include "King.h"

typedef std::pair<Square*, Square*> Move;

class Game{
    
private:
    Board* board;
    int movesMade;
    bool inBounds(int r, int c) const;
    int turn;
    std::vector<Player*>* playerList;
    void notifyAllKings();
    
    
public:
    Game(Board* , std::vector<Player*>* , int);
    ~Game();
    Board* getBoard() const;
    void doMove(Square*, Square*);
    double play();
    int numPlayers() const;
    Player* getPlayer(int color) const;

};

#endif /* defined(__chess__Game__) */
