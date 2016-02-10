//
//  Square.cc
//  chess
//
//  Created by User on 2015-11-25.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#include "Square.h"
//#include "Piece.h"

using namespace std;

ostream& operator<<(ostream& out, const Square& s) {
    out << (Chess::MAPPING[s . getColumn()]);
    out << (8-s . getRow());
    return out;
}

ostream& Square::operator<<(ostream& out) const{
    out << (Chess::MAPPING[getColumn()]);
    out << (getRow());
    return out;
}

Square::Square(int row, int col) : row(row), col(col){
    p = NULL;
    controllers = new std::set<Square*>;
}

double Square::controlValue() const{
    return 0.0;
}

int Square::getRow() const{
    return row;
}

int Square::getColumn() const{
    return col;
}

Piece* Square::setPiece(Piece* newPiece){

    Piece* toReturn = p;
    p = newPiece;
    return toReturn;
    
}

std::set<Square*>* Square::getControllers() const{
    return controllers;
}

Piece* Square::piece() const{
    return p;
}


void Square::addController(Square * s){
    //std::cout << " ~~~~~~~~~~ " << *this << " is now controlled by " << *s << std::endl;
    controllers -> insert(s);
}

void Square::removeController(Square* s){
    //the line below is confusiong and I hate c++, but:
    //basically, erase the iterator which points to the found location of p
    std::set<Square*>::iterator it = controllers -> find(s);
    //std::cout << " --> Have the iterator from find(p)...\n";
    if(it != controllers -> end()){
     //   std::cout << "--> iterator of find(p) doesn't point to end" << std::endl;
        controllers -> erase(it);
        //std::cout << "IN CONTROLLER REMOVAL!" << std::endl;
       // std::cout << p -> getPieceID() << " no longer controls " << *this << std::endl;
    }
    //std::cout << "REMOVING A CONTROLLER IS NOT SUPPORTED." << std::endl;
    
}


void Square::printInfoTo(std::ostream& out) const{
    //std::set<Piece*> controllers = s -> getControllers();
    for(set<Square*>::iterator it = controllers -> begin(); it != controllers -> end(); ++it){
        cout << *(*it) << endl;
    }
}


Square::~Square(){
    std::cout << "***************** SQUARE DESTRUCTOR *********************\n";
    while(!(controllers -> empty()))
        controllers -> clear();
    delete controllers;
    p = NULL;
    controllers = NULL;
}

