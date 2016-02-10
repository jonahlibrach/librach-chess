//
//  main.cpp
//  chess
//
//  Created by User on 2015-11-23.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <set>
#include <vector>

#include "Game.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

#include "Player.h"
#include "Human.h"
#include "AI.h"

#define p1 player=0;
#define p2 player=1;

class Piece;
//this changed.
using namespace std;

Piece* pieceFactory(char c){
    if(c == 'k' || c == 'K'){
        return new King(c);
    }
    else if(c == 'q' || c == 'Q'){
        return new Queen(c);
    }
    else if(c == 'r' || c == 'R'){
        return new Rook(c);
    }
    else if(c == 'b' || c == 'B'){
        return new Bishop(c);
    }else if(c == 'n' || c == 'N'){
        return new Knight(c);
    }else if(c == 'p' || c == 'P'){
        return new Pawn(c);
    }
    return NULL;
}

typedef map < char, set<Piece*> > PieceSet;

int main(int argc, const char * argv[]){
    
    std::string STANDARD_BOARD = "standard_board.txt";
    std::string PIECE_SETUP = argc == 2 ? argv[1] :  "standard_setup.txt";
    double white = 0, black = 0;
    
    Board* board = NULL;
    PieceSet* container = NULL;
    int turn;
    bool setupDone = false;
    string command;
    while(cin >> command){
       // std::cout << "Command: " << command << std::endl;

        if(cin.eof())
            cout << "END OF FILE" << endl;
        
        if(command.substr(0,5) == "setup"){
            std::cout << "Setup Mode: [+,-,=,done]\n";
            delete container;
            delete board;
            //int players = 2;
            if(command.length() != 5){
                std::cout << "\n--> UNSUPPORTED COMMAND <--\n";
            }else{
        
                board = new Board(STANDARD_BOARD);
                container = new PieceSet;
                turn = board -> initSetup(cin, PIECE_SETUP, &pieceFactory, container);
                setupDone = true;
            }
            
        }
        
        else if(command == "game"){
            string line;
            getline(cin, line);
            std::vector<Player*> playerList;
            istringstream iss(line);
            while(true){
                string userType;
                iss >> userType;
                if(iss.fail())
                    break;
                if(userType == "human"){
                    
                    Human* human = new Human(playerList.size(), std::cin);
                    playerList.insert(playerList.end(), human);
                   
                    
                }else if(userType.find("computer") == 0){
                    istringstream levelStream(userType);
                    int level = 1;
                    while(!(levelStream >> level)){
                        if(levelStream.eof()){
                            cout << "Weird input.\n";
                            continue;
                        }
                        if(levelStream.fail()){
                            levelStream.clear();
                            levelStream.ignore();
                        }

                    }
                
                    cout << "Requested computer level " << level << "\n";
                    
                    AI* ai = new AI(level, playerList.size());
                    playerList.insert(playerList.end(), ai);

                }
                if(!setupDone){
                    std::cout << "Game setup required." << std::endl;
                    continue;
                }
                else if(playerList.size() == 2){
                    Game g(board, &playerList, turn);
                    double result = g.play();
                    if(result == 0.5){
                        white += result;
                        black += result;
                    }else if(result){
                        black++;
                    }else{
                        white++;
                    }
                    setupDone = false;
                }
            }//end while for reading game command
        }
    }
        cout << "Final score:\n";
        cout << "White: " << white << "\n";
        cout << "Black: " << black << "\n";
}
