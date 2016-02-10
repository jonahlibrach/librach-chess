//
//  Game.cc
//  chess
//
//  Created by User on 2015-11-25.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#include "Game.h"


Game::Game(Board* b, std::vector<Player*>* playerList, int whoStarts) : board(b), playerList(playerList), turn(whoStarts){
    for(int i = 0; i < playerList -> size(); i++){
        playerList -> at(i) -> setGame(this);
    }
    
    for(int i = 0; i < b->getRows(); i++){
        for(int j = 0; j < b -> getColumns(); j++){
            Square* s = b -> getSquare(i, j);
            if(s && s -> piece()){
                Piece* piece = s -> piece();
                int playerNum = piece -> getColor();
                Player* player = playerList -> at(playerNum);
                piece -> setPlayer(player);
                player -> addPiece(piece);
            }
        }
    }
    
    
}

Player* Game::getPlayer(int color) const{
    return playerList -> at(color);
}

Game::~Game(){}

void Game::doMove(Square* from, Square* to){
    //this method does not check for move validity, that should likely be done in the pieces.
    
    //move piece
    Piece* toMove = board -> replacePiece(from, NULL);
    
    //check if castling
    if(dynamic_cast<King*>(toMove)){
        int dir = to -> getColumn() - from -> getColumn();
        if(std::abs(dir) == 2){
            dir = dir < 0 ? -1 : 1;
            Square* rookFrom = (board -> board)[from -> getRow()][dir < 0 ? 0 : 7];
            Square* rookTo = board -> board[from -> getRow()][from -> getColumn() + dir];
            toMove -> setMoved(true);
            doMove(rookFrom, rookTo);
        }
    }
    
    Piece* captured = board -> replacePiece(to, toMove);
    //cout << "Captured is " << (captured ? " not " : "") << " null." << std::endl;
    if(captured)
        playerList -> at(captured -> getColor()) -> destroy(captured);
    
    toMove -> setMoved(true);
    
}

int Game::numPlayers() const{
    return playerList -> size();
}

Board* Game::getBoard() const{
    return board;
}

void Game::notifyAllKings(){
    for(int i = 0; i < 2; i++){
        Piece* p = playerList -> at(i) -> getKing();
        p -> reset();
        p -> calibrate();
    }
}

double Game::play(){
    std::cout << "Playing game." << std::endl;
    
    for(int i = 0; i < 4; i++){
        playerList -> at(i%2) -> calibrate();
    }
    
    Player* currentPlayer = playerList -> at(turn);
    Move* move;
    Piece* currentPlayerKing = playerList -> at(turn) -> getKing();
    Square* cpkSquare = currentPlayerKing -> getSquare();
    
    //check if the move went through.. if not the game is over!
    while((move = currentPlayer -> makeMove(board, currentPlayer -> getMoveList()))){
        
        if(board -> isControlledByEnemiesOf(currentPlayerKing, cpkSquare))
            std::cout << (turn ? "Black" : "White") << " is in check." << std::endl;
        
        doMove(move->first, move->second);
        turn = (turn+1)%(numPlayers());
        currentPlayer = playerList -> at(turn);
        
        currentPlayerKing = playerList -> at(turn) -> getKing();
        cpkSquare = currentPlayerKing -> getSquare();
        
        
        
        for(int i = 0; i < 4; i++){
            playerList -> at(i%2) -> calibrate();
        }
        board -> printTo(cout);
    }//end game loop
    
    if (playerList -> at(turn) -> resigned()){
        std::cout << (turn ? "White" : "Black") << " resigned." << std::endl;
        return turn;
    }
    else if(board -> isControlledByEnemiesOf(currentPlayerKing, cpkSquare)){
        cout << "Checkmate! " << (turn ? "White" : "Black") << " wins!\n";
        return !turn;
    }else{
        cout << "Stalemate!\n";
        return 0.5;
    }
    
    
}

