//
//  Human.cc
//  chess
//
//  Created by User on 2015-11-23.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#include "Human.h"

using namespace std;

Human::Human(int playerNumber, std::istream& in) : Player(playerNumber), input(&in){
    
}

Human::~Human(){
    
}

bool Human::findMove(Move* move, set<Move*>* moveList) const{
    set<Move*>::iterator it = moveList -> begin();
    for( ; it != moveList -> end(); ++it){
        if(**it == *move)
            return true;
    }
    return false;
}

void Human::printHint(set<Move*>* moveList) const{
    srand(time(NULL));
    int move = rand() % moveList -> size();
    
    std::set<Move*>::iterator it = moveList -> begin();
    for(int i = 0; it != moveList -> end(); ++it, i++){
        if(i == move){
            std::cout << "HINT: " << *((*it) -> first) << " --> " << *((*it) -> second) << "\n";
        }
    }
}


Move* Human::makeMove(Board* board, std::set<Move*>* moveList){
    //std::cout << "There are " << moveList -> size() << " moves possible for player " << getPlayerID() << "\n";
    if(moveList -> size() == 0){
        delete moveList;
        return NULL;
    }
    Move* move = NULL;
    std::cout << "Human move: " << std::endl;
    std::string cmd;
    while(!rsgned && !move){
        *input >> cmd;
    if(cmd == "resign"){
        rsgned = true;
    }
    else if(cmd == "move"){
        *input >> cmd;
        Square* sq1 = board -> getSquare(cmd);
        *input >> cmd;
        Square* sq2 = board -> getSquare(cmd);
        move = new Move;
        move -> first = sq1;
        move -> second = sq2;
        if(! ( sq1 && sq2 && findMove(move, moveList)) ) {
            std::cout << "Illegal Move Entered." << std::endl;
            delete move;
            move = NULL;
        }
    }
    else if(cmd == "info"){
        *input >> cmd;
        std::cout << "Info for " << cmd << ".\n";
        Square* square = board -> getSquare(cmd);
        if(square)
            square -> printInfoTo(cout);
        if(square -> piece())
            square -> piece() -> printLegalMovesTo(cout);
    }else if(cmd == "hint"){
        printHint(moveList);
    }
        input -> clear();
        input -> ignore();
        
    }
    //cout << "Move made successfully." << endl;
    return move;
}

