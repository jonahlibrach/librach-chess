//
//  Board.h
//  chess
//
//  Created by User on 2015-11-23.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#ifndef __chess__Board__
#define __chess__Board__



#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <list>
#include "Piece.h"
#include "Square.h"



using namespace std;

typedef map< char, set<Piece*> > PieceSet;


class Board{
    
    friend class Piece;
    map<char, int>* rowMap;
    map<char, int>* columnMap;
    PieceSet* pieceSet;
    
private:
    
    bool settingUp;
    int rows, cols;
    void setupBoardStructure(std::string&);
    void loadGame(std::string&);
    char squareChar(Square*) const;
public:
    Square*** board;
    ~Board();
    Board(std::string&);
    bool isControlledByEnemiesOf(Piece*, Square*) const;
    std::set<Square*>* enemyControllersOf(Piece*, Square*) const;
    
    bool inSetup();
    int initSetup(istream&, std::string&, Piece* (pieceFactory)(char), PieceSet*);
    Piece* findPiece(char) const;
    bool*** getBoolEquivalent();
    Piece* replacePiece(Square*, Piece*);
    bool endSetup();
    void printTo(std::ostream&) const;
    void notifyChange(Square*);
    int getRows() const;
    int getColumns() const;
    void draw();
    void draw(int, int);
    Square* getSquare(int row, int column) const;
    Square* getSquare(std::string squareID) const;
    
    
};

#endif /* defined(__chess__Board__) */
