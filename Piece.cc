//
//  Piece.cpp
//  chess
//
//  Created by User on 2015-11-23.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//


#include "Piece.h"

/*bool CalibCompare::operator()(Piece* lhs, Piece* rhs){
    return lhs -> getColor() != rhs -> getColor();
}*/

Piece::Piece(char c){
    this -> c = c;
    board = NULL;
    sq = NULL;
    moved = false;
    player = NULL;
    moveList = new std::set<Move*>;
    controlList = new std::set<Square*>;
}

Piece::~Piece(){
    moveList -> clear();
    delete moveList;
    delete validMoves;
    delete sight;
    delete control;
    
}


void Piece::printCalibration() const{
    //std::cout << "\033[1;31m" << "Calibrating " << getPieceID() << " - " << *getSquare() << "\033[0m\n";
}

int Piece::getColor() const{
    
    if(c == 'p' || c == 'r' || c == 'b' || c == 'n' || c == 'q' || c == 'k'){
        return 1;
    }else if(c == 'P' || c == 'R' || c == 'B' || c == 'N' || c == 'Q' || c == 'K'){
        return 0;
    }else
        return -1;
}

char Piece::getPieceID() const{
    return c;
}

void Piece::setPlayer(Player* p){
    this -> player = p;
}

Player* Piece::getPlayer() const{
    return player;
}

void Piece::setBoard(Board* b){
    this -> board = b;
    validMoves = b -> getBoolEquivalent();
    control = b -> getBoolEquivalent();
    sight = b -> getBoolEquivalent();
    
}

Board* Piece::getBoard() const{
    return board;
}

void Piece::enableControl(Square* toControl, bool enabled){
    
    //its assumed that this square exists on the board, otherwise everything
    //gets screwed up... (it wouldn't hurt to ensure though...)
   // std::cout << "enableControl: " << enabled << std::endl;
    *control[sq->getRow()][sq->getColumn()] = enabled;
    if(enabled){
        toControl -> addController(sq);
        controlList -> insert(toControl);
    }else{
        toControl -> removeController(sq);
    }
    //std::cout << "enableControl success: " << enabled << std::endl;
}

void Piece::enableMove(Square* to, bool enabled){
    //also assuming this move is valid so not checking the squares to which
    //it pertains
   // std::cout << "enableMove: " << enabled << std::endl;
    if(enabled){
        Move* move = new Move;
        move -> first = this -> sq;
        move -> second = to;
        moveList -> insert(move);
    }else
        
    *validMoves[sq -> getRow()][sq -> getColumn()] = enabled;
   // std::cout << "enabledMove success: " << enabled << std::endl;
}

std::set<Move*>* Piece::getLegalMoves() const{
    return moveList;
}

void Piece::printLegalMovesTo(ostream& out) const {
    std::set<Move*>::iterator it;
    cout << "******* LEGAL MOVES **********\n";
    for(it = moveList->begin(); it != moveList -> end(); ++it){
        std::cout << *(*it) -> first << " --> " << *(*it) -> second << "\n";
    }
    cout << "*****************************\n";
}

void Piece::enableSight(Square* sq, bool enabled){
   // std::cout << "enableSight: " << enabled << std::endl;
    *sight[sq->getRow()][sq->getColumn()] = enabled;
   // std::cout << "enableSight success: " << enabled << std::endl;
}

bool Piece::hasMoved() const{
    return moved;
}

bool Piece::hasMove(Square* to) const{
    set<Move*>::iterator it;
    for(it = moveList -> begin(); it != moveList -> end(); ++it){
        if((*it) -> second  == to)
            return true;
    }
    return false;
}

bool Piece::hasControl(int row, int col) const{
    if(control && control [row][col] )
        return *control[row][col];
    return false;
}

bool Piece::hasControl(Square* sq) const{
    return hasControl(sq -> getRow(), sq -> getColumn());
}

bool Piece::hasSight(int row, int col) const{
    if(sight && sight[row][col])
        return *sight[row][col];
    return false;
}

bool Piece::hasSight(Square* sq) const{
    return hasSight(sq -> getRow(), sq -> getColumn());
}

void Piece::setSquare(Square* square){
    this -> sq = square;
}

Square* Piece::getSquare() const{
    return sq;
}

void Piece::setMoved(bool moved){
    this -> moved = moved;
   // std::cout << getPieceID() << " has moved? " << this -> moved << std::endl;
}

void Piece::reset(){
   // std::cout << "Resetting " << getPieceID() << std::endl;
    moveList -> clear();
    delete moveList;
    moveList = new std::set<Move*>;
    
    std::set<Square*>::iterator it = controlList -> begin();
    for(it = controlList -> begin(); it != controlList -> end(); ++it){
        enableControl(*it, false);
    }
    controlList -> clear();
    
}

void printArr(bool*** b, std::ostream& out){
    bool lastNull = true;
    int i = 0, j = 0;
    while(true){
            try{
                out << *b[i][j];
                lastNull = false;
                j++;
            }catch(int e){
                out<<"\n";
                i++;
                if(lastNull)
                    break;
            }
        }
        
    }

void Piece::printInfoTo(std::ostream& out) const{

    out << "**** SIGHT ****\n";
    printArr(sight, out);
    out << "***************\n";
    out << "**** CONTROL ****\n";
    printArr(control, out);
    out << "******************\n";
    out << "**** VALID MOVES ****\n";
    for(std::set<Move*>::iterator it = moveList -> begin(); it != moveList -> end(); ++it)
        out << *it << " ";
    out << "\n";
    out << "*********************\n";
}