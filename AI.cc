//
//  AI.cc
//  chess
//
//  Created by User on 2015-11-23.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#include "AI.h"
#define BOLDRED     "\033[1m\033[31m"

bool AI::isDiagCheck(Board* board, Square* toMove, Piece* king) const{
    int r = king -> getSquare() -> getRow();
    int c = king -> getSquare() -> getColumn();
    for(int i = 0; i < 4; i++){
        bool pieceSeen = false;
        for(int k = 0; k < 8 && !pieceSeen; k++){
            
            Square* potCheck = board -> getSquare(Chess::DIAGONAL[i][0] * k + r, Chess::DIAGONAL[i][0] * k + c);
            
            if(potCheck){
                pieceSeen = potCheck -> piece();
                if(toMove == potCheck)
                    return true;
            }
        }
    }
    return false;
    
}

bool AI::isVertCheck(Board* board, Square* toMove, Piece* king) const{
    int r = king -> getSquare() -> getRow();
    int c = king -> getSquare() -> getColumn();
    for(int i = 0; i < 4; i++){
        bool pieceSeen = false;
        for(int k = 0; k < 8 && !pieceSeen; k++){
            
            Square* potCheck = board -> getSquare(Chess::ADJACENT[i][0] * k + r, Chess::ADJACENT[i][0] * k + c);
            if(potCheck){
                pieceSeen = potCheck -> piece();
                if(toMove == potCheck)
                    return true;
            }
        }
    }
    return false;
}

bool AI::isKnightCheck(Board* b, Square* toMove, Piece* king) const{
    int r = king -> getSquare() -> getRow();
    int c = king -> getSquare() -> getColumn();
    for(int i = 0; i < 8; i++){
        Square* potCheck = b -> getSquare(Chess::KNIGHT[i][0] + r, Chess::KNIGHT[i][1] + c);
        if(potCheck){
            if(toMove == potCheck)
                return true;
        }
    }
    return false;
}


Move* AI::canMovePiece(string wanted, Square* to) const{
    set<Piece*>::iterator it;
    for(it = pieces -> begin(); it != pieces -> end(); ++it){
        
        if(wanted.find((*it) -> getPieceID()) != string::npos){
            if((*it) -> hasMove(to)){
                Move* m = new Move;
                m -> first = (*it) -> getSquare();
                m -> second = to;
                return m;
            }
            
        }
    }

    return NULL;
    
}

bool AI::lessThan(Move* lhs, Move* rhs, Board* board) const{
    
    //we want to avoid our best pieces being caputred
    //also, we don't want to 'avoid a capture' by moving to
    //a square where we can get captured.
    //when deciding between general moves, chose towards the centre
    
    //look to avoid captures of higher valued pieces
    
    //look to capture higher valued pieces
    //if the piece gives check, that's a plus (not in general but for this assignment)
    
    /*
    Ranking: 
     
     1. Avoid capture of best piece.
     2. Capture best piece. 
     3. Give check. 
     4. Move towards the middle.
    
    */
    
    //comparison 1: check if they are about to be caputred
    Piece* left = lhs -> first -> piece();
    Piece* leftAttack = lhs -> second -> piece();
    bool leftRecapturable = board -> isControlledByEnemiesOf(left, lhs -> second);
    Piece* right = rhs -> first -> piece();
    Piece* rightAttack = rhs -> second -> piece();
    bool rightRecaptureable = board -> isControlledByEnemiesOf(right, rhs -> second);
    
    double pll = (left -> getMaterialValue()) * leftRecapturable; //potential loss left
    double gainLeft = leftAttack ? leftAttack -> getMaterialValue() : 0;
    double plr = (right -> getMaterialValue()) * rightRecaptureable; //^ ^ right
    double gainRight = rightAttack ? rightAttack -> getMaterialValue() : 0;
    double netGainLeft = gainLeft - pll;
    double netGainRight = gainRight - plr;
    
    if(netGainLeft != netGainRight){
        std::cout << "FOR MOVE BELOW MATERIAL LOSS: (" << netGainLeft << " vs " << netGainRight << ")\n";
        return netGainLeft < netGainRight;
    }
    
    //assign giving check a value of 2
    Piece* enemyKing = board -> findPiece(getPlayerID() ? 'K' : 'k');
    if(left -> getPieceID() == 'N' || left -> getPieceID() == 'n'){
        netGainLeft += 2 * isKnightCheck(board, lhs -> second, enemyKing);
    }else if(left -> getPieceID() == 'B' || left -> getPieceID() == 'b'){
        netGainLeft += 2 * isDiagCheck(board, lhs -> second, enemyKing);
    }else if(left -> getPieceID() == 'R' || left -> getPieceID() == 'r'){
        netGainLeft += 2 * isVertCheck(board, lhs -> second, enemyKing);
    }else if(left -> getPieceID() == 'Q' || left -> getPieceID() == 'q'){
        netGainLeft += 2 * isVertCheck(board, lhs -> second, enemyKing);
        netGainLeft += 2 * isDiagCheck(board, lhs -> second, enemyKing);
    }
    
    if(right -> getPieceID() == 'N' || right -> getPieceID() == 'n'){
        netGainRight += 2 * isKnightCheck(board, rhs -> second, enemyKing);
    }else if(right -> getPieceID() == 'B' || right -> getPieceID() == 'b'){
        netGainRight += 2 * isDiagCheck(board, rhs -> second, enemyKing);
    }else if(right -> getPieceID() == 'R' || right -> getPieceID() == 'r'){
        netGainRight += 2 * isVertCheck(board, rhs -> second, enemyKing);
    }else if(right -> getPieceID() == 'Q' || right -> getPieceID() == 'q'){
        netGainRight += 2 * isVertCheck(board, rhs -> second, enemyKing);
        netGainRight += 2 * isDiagCheck(board, rhs -> second, enemyKing);
    }
    
    
    if(netGainLeft != netGainRight){
        std::cout << "FOR MOVE BELOW MATERIAL GAIN: (" << netGainLeft << " vs " << netGainRight << ")\n";
        
        return netGainLeft < netGainRight;
    }
    
    //lastly, check how centered the move is
    Square* ls = lhs -> second;
    Square* rs = rhs -> second;
    int locLHS = Chess::LOCATION_VALUE[ls -> getRow()][ls -> getColumn()];
    int locRHS = Chess::LOCATION_VALUE[rs -> getRow()][rs -> getColumn()];

    std::cout << "LOCATION DETERMINES: (" << locLHS << " vs " << locRHS << ")\n";
    return locLHS < locRHS;
    
    
    
}

AI::AI(int level, int playerNumber) : Player(playerNumber), level(level){

}

AI::~AI(){}

Move* AI::levelOne(set<Move*>* moves) const{
   
    srand(NULL);
    int random = rand() % (moves -> size());
    
   
    set<Move*>::iterator it;
    int i = 0;
    Move* toReturn = NULL;
    for(it = moves -> begin(); !toReturn && it != moves -> end(); ++it){
        
        if(i == random){
            return *it;
        }
        i++;
    }
    return toReturn;
}

Move* AI::levelTwo(Board* board, set<Move*>* moves) const{
    
    //find checks
    Piece* enemyKing = board -> findPiece(getPlayerID() ? 'K' : 'k');
    int r = enemyKing -> getSquare() -> getRow();
    int c = enemyKing -> getSquare() -> getColumn();
    for(int i = 0; i < 8; i++){
        Square* to =board -> getSquare(Chess::KNIGHT[i][0] + r, Chess::KNIGHT[i][1] + c);
        if(to){
            Move* m = canMovePiece("nN", to);
            if(m)
                return m;
        }
    }
    
    
    
    for(int i = 0; i < 4; i++){
        bool pieceSeen = false;
        for(int k = 0; k < 8 && !pieceSeen; k++){
        
            Square* to = board -> getSquare(Chess::ADJACENT[i][0] * k + r, Chess::ADJACENT[i][0] * k + c);
            if(to){
                if(to ->piece())
                    pieceSeen = true;
                Move* m = canMovePiece("rRqQ", to);
                if(m)
                    return m;
            }
        }
    }
    
    
    for(int i = 0; i < 4; i++){
        bool pieceSeen = false;
        for(int k = 0; k < 8 && !pieceSeen; k++){
            
            Square* to = board -> getSquare(Chess::DIAGONAL[i][0] * k + r, Chess::DIAGONAL[i][0] * k + c);
            if(to){
                if(to ->piece())
                    pieceSeen = true;
                Move* m = canMovePiece("bBqQ", to);
                if(m)
                    return m;
            }
        }
    }
    
    //then find captures
    set<Move*>::iterator it;
    for(it = moves -> begin(); it != moves -> end(); ++it){
        if((*it) -> second -> piece())
            return *it;
    }
    //if no captures, move randomly
    return levelOne(moves);

}

Move* AI::levelThree(Board* board, set<Move*>* moves) const{
    //first avoids captures, then calls level 2 for the other functionalities
    //its not looking ahead into the future
    //does not do all three (as in the level above)
    //LEVEL 2:
        //then finds checks
        //then captures
    
    set<Move*>::iterator it;
    for(it = moves -> begin(); it != moves -> end(); ++it){
        Square* curSquare = (*it) -> first;
        Piece* toMove = curSquare -> piece();
        if(board -> isControlledByEnemiesOf(toMove, curSquare))
            return *it;
    }
    
    return levelTwo(board, moves);
    
}

Move* AI::levelFour(Board* board, set<Move*>* moves) const{
    Move* bestMove = NULL;
    set<Move*>::iterator it;
    for(it = moves -> begin(); it != moves -> end(); ++it){
        if(!bestMove)
            bestMove = *it;
        else{
            if(lessThan(bestMove, *it, board)){
                std::cout << "\t" << BOLDBLUE << *(*it) -> first << " -> " << *(*it) -> second << " > ";
                std::cout << *bestMove -> first << " -> " << *bestMove -> second << RESET << endl;
                bestMove = *it;
            }else{
                std::cout << "\t" << BOLDRED << *(*it) -> first << " -> " << *(*it) -> second << " <= ";
                std::cout << *bestMove -> first << " -> " << *bestMove -> second << RESET << endl;
            }
        }
    }
    return bestMove;
}

Move* AI::makeMove(Board* b, set<Move*>* moves){

    std::string goAhead("");

    while(cin >> goAhead && goAhead != "move");

    if(moves -> size() == 0)
        return NULL;
    
    if(level == 1){
        return levelOne(moves);
    }else if(level == 2){
        return levelTwo(b, moves);
    }else if(level == 3){
        return levelThree(b, moves);
    }else if(level == 4){
        return levelFour(b, moves);
    }
    //etc..
    return NULL;
}

    
    
