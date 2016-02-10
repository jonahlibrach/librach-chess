//
//  Player.h
//  chess
//
//  Created by User on 2015-11-23.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#ifndef chess_Player_h
#define chess_Player_h

#include "Board.h"
#include <string>
#include <set>


class Piece;
class Game;
class Board;
class King;

typedef std::pair<Square*,Square*> Move;

class Player{
protected:
    std::set<Piece*>* pieces;
    bool check;
    bool rsgned;
    int playerNumber;
    Game* game;
    
    
public:
    Player(int);
    virtual ~Player();
    virtual Move* makeMove(Board* b, std::set<Move*>*) = 0;
    std::set<Move*>* getMoveList();
    void notifyCheck();
    void notifyKing();
    Piece* getKing() const;
    void destroy(Piece*);
    void addPiece(Piece*);
    void setGame(Game*);
    void calibrate();
    Game* getGame() const;
    bool inCheck() const;
    bool resigned() const;
    int getPlayerID() const;
    
    
    
    
};

#endif
