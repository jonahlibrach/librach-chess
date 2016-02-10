//
//  Rook.cpp
//  chess
//
//  Created by User on 2015-11-25.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

//
//  Rook.cpp
//  chess
//
//  Created by User on 2015-11-25.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#include "Rook.h"

Rook::Rook(char c) : Piece(c) {
    //type = "rook";
}

double Rook::getMaterialValue() const{
    return 0.0;
}

void Rook::calibrate(){
    if(!player)
        return;
    printCalibration();
    if(board){
        
        for(int i = 0; i < 4; i++){
            int piecesSeen = 0;
            for(int k = 1; k < 8 && piecesSeen < 2; k++){
                int adjI = Chess::ADJACENT[i][0] * k + sq -> getRow();
                int adjJ = Chess::ADJACENT[i][1] * k + sq -> getColumn();
                Square* adj = board -> getSquare(adjI, adjJ);
                if(adj){
                    //std::cout << " ****** Looking at: " << *adj << "\n";
                    enableSight(adj, true);
                    enableControl(adj, piecesSeen == 0);
                    enableSight(adj, true);
                    enableControl(adj, piecesSeen == 0);
                    if(adj -> piece()){
                        if(adj -> piece() -> getColor() != getColor()){
                            King* k = static_cast<King*>(getPlayer() -> getKing());
                            bool movePermission = k -> requestPermission(getSquare(), adj);
                            enableMove(adj, piecesSeen == 0 && movePermission);
                        }
                        //if the piece is not a king and the piece is the opponent's piece
                        //in other words (piece is not the opponent's king
                        if(!(dynamic_cast<King*>(adj->piece()) && adj->piece()->getColor() != getColor()))
                            piecesSeen++;
                    }else{
                        King* k = static_cast<King*>(getPlayer() -> getKing());
                        bool movePermission = k -> requestPermission(getSquare(), adj);
                        enableMove(adj, piecesSeen == 0 && movePermission);
                    }
                }
            }
        }
    }
     //std::cout << "Calibration success." << std::endl;
}
