//
//  main.cpp
//  chess
//
//  Created by User on 2015-11-23.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <vector>
#include "Chess.h"
#include "Player.h"
#include "Human.h"
#include "AI.h"

#define p1 player=0;
#define p2 player=1;


using namespace std;

Piece* processPiece(int& c, int player){
        Piece

}

void organizePieces(std::string& gameState, Board* board, list<Piece*>* gamePieces){
    ifstream positionReader(gameState);
    
    char c;
    while(positionReader >> c && !positionReader.eof()){
        
        if(c != '_'){
            int player = -1;
            Piece* piece = Chess::pieceFactory(c);
            gamePieces -> push_front(piece);
        }
        
    }
    
}

int main(int argc, const char * argv[]) {
    
    std::string STANDARD_BOARD = "standard_board.txt";
    std::string STANDARD_PIECE_SETUP = "standard_setup.txt";
    
    std::cout << "Setting up board." << std::endl;
    Board* board;
    list<Piece>* pieceContainer;
    std::cout << "Board setup complete." << std::endl;
    board -> printTo(std::cout);
    string command;
    while(cin >> command){
        
        if(cin.eof())
            cout << "END OF FILE" << endl;
        
        if(command.substr(0,4) == "setup"){
            delete pieceContainer;
            delete board;
            int players = 2;
            if(command.length() != 5){
                std::cout << "\n--> UNSUPPORTED COMMAND <--\n";
            }else{
        
                board = new Board(STANDARD_BOARD);
                pieceContainer = new list<Piece>[players];
                organizePieces(STANDARD_PIECE_SETUP, board, pieceContainer);
            }
            /*
             The interpretation is that setup mode initializes a new board in
             the standard starting position. If setup is called before a new 
             game starts, then the previous board is deleted with 'delete board' 
             and a new board is created with standard starting positions.
             */
        }
        
        else if(command == "game"){
            string line;
            getline(cin, line);
            std::vector<Player> playerList;
            istringstream iss(line);
            while(true){
                string userType;
                iss >> userType;
                if(iss.fail())
                    break;
                if(userType == "human"){
                   /* Human human;
                    playerList.push_back(human);*/
                    
                }else if(userType.substr(0,8) == "computer"){
                   /*
                    ostringstream oss(userType);
                    if(userType[10] < '1' || userType[10] > '4'){
                        cout << "Illegal Level";
                    }
                    cout << "Recevied computer level " << userType[10] << endl;
                    AI ai(userType[10]-48);
                }
                */
                
                }
                return 1;
            }
        }
    }
}
