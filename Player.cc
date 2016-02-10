//
//  Player.cc
//  chess
//
//  Created by User on 2015-11-30.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#include "Player.h"


Player::Player(int playerNumber){
    check = false;
    rsgned = false;
    game = NULL;
    this -> playerNumber = playerNumber;
    pieces = new std::set<Piece*>;
}

Player::~Player(){
    
}

int Player::getPlayerID() const{
    return playerNumber;
}

Game* Player::getGame() const{
    return game;
}

Piece* Player::getKing() const{
    std::set<Piece*>::iterator it;
    for(it = pieces -> begin(); it != pieces -> end(); ++it){
        if((*it) -> getPieceID() == 'K' || (*it) -> getPieceID() == 'k')
            return *it;
    }
    return NULL;
}

void Player::destroy(Piece* toDestroy){
    if(toDestroy){
        
        pieces -> erase(toDestroy);
        delete toDestroy;
        
    }
}

void Player::addPiece(Piece* p){
    //std::cout << p -> getPieceID() << " assigned to player " << getPlayerID() << std::endl;
    pieces -> insert(p);
}

void Player::setGame(Game* game){
    this -> game = game;
}

bool Player::inCheck() const{
    return check;
}

bool Player::resigned() const{
    return rsgned;
}

void Player::calibrate(){
   // std::cout << "Calibrating player " << getPlayerID() << std::endl;
   // if(forward){
    std::set<Piece*>::iterator it;
    for(it = pieces -> begin(); it != pieces -> end(); ++it){
        (*it) -> reset();
        (*it) -> calibrate();
   /* }
    }else{
    std::set<Piece*>::reverse_iterator rit;
    for(rit = pieces -> rbegin(); rit != pieces -> rend(); ++rit)
        (*rit) -> calibrate();
    }*/
}
}

std::set<Move*>* Player::getMoveList(){
    
    std::set<Move*>* moveList = new std::set<Move*>;
    
    std::set<Piece*>::iterator it;
    for(it = pieces -> begin(); it != pieces -> end(); ++it){
        std::set<Move*>* pieceMoves = (*it) -> getLegalMoves();
        if((*it) -> getColor() != getPlayerID()){
            while(true){
                cout << "YOU HAVE A BUG!" << endl;
            }
        }
        moveList -> insert(pieceMoves -> begin(), pieceMoves -> end());
    }
    return moveList;
}
