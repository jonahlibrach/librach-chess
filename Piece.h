//
//  Piece.h
//  chess
//
//  Created by User on 2015-11-23.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#ifndef __chess__Piece__
#define __chess__Piece__

class Board;
class Square;

#import "Board.h"
#import "Player.h"
#include <iostream>
#include <set>

class Player;

namespace Settings{
   static const int CLEAR = -1;
   static const int SIGHT = 2;
   static const int CONTROL = 3;
   static const int CAN_MOVE = 5;
    
};

/*class CalibCompare{
public:
    bool operator() (Piece*, Piece*);
};*/

typedef std::pair<Square*, Square*> Move;
class Piece{
    
    friend class Board;
    
protected:
    int color;
    bool moved;
    Board* board;
    Player* player;
    std::set<Move*>* moveList;
    std::set<Square*>* controlList;
    Square* sq;
    bool*** validMoves;
    bool*** control;
    bool*** sight;
    unsigned char c;
    void enableMove(Square*, bool);
    void enableControl(Square*, bool);
    void enableSight(Square*, bool);

public:
    virtual std::string unicode() const = 0;
    std::set<Move*>* getLegalMoves() const;
    int getColor() const;
    Square* getSquare() const;
    void printInfoTo(std::ostream&) const;
    Board* getBoard() const;
    char getPieceID() const;
    void setBoard(Board*);
    void setSquare(Square*);
    void setPlayer(Player*);
    Player* getPlayer() const;
    virtual void setMoved(bool);
   // virtual std::string& getType() const = 0;
    bool hasMoved() const;
    //virtual bool hasMove(int row, int col)const;
    virtual bool hasMove(Square*) const;
    virtual bool hasControl(int row, int col) const;
    virtual bool hasControl(Square*) const;
    virtual bool hasSight(int row, int col) const;
    virtual bool hasSight(Square*) const;

    void printLegalMovesTo(std::ostream&) const;
    
    Piece(char);
    virtual ~Piece();
    virtual double getMaterialValue() const = 0;
    void printCalibration() const;
    virtual void calibrate() = 0;
    virtual void reset();

    
    
};

#endif /* defined(__chess__Piece__) */