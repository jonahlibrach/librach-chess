//
//  Queen.cpp
//  chess
//
//  Created by User on 2015-11-25.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#include "Queen.h"

Queen::Queen(char c) : Piece(c) {
}

double Queen::getMaterialValue() const{
    return 9.0;
}

std::string Queen::unicode() const{
    return (getColor() ? "\u265B" : "\u2655");
}

void Queen::calibrate(){
    if(!player)
        return;
    printCalibration();
    if(board){
        
        
        for(int d = 0; d < 2; d++)
        for(int i = 0; i < 4; i++){
            int piecesSeen = 0;
            for(int k = 1; k < 8 && piecesSeen < 2; k++){
                int adjI = Chess::ALL_DIRS[d][i][0] * k + sq -> getRow();
                int adjJ = Chess::ALL_DIRS[d][i][1] * k + sq -> getColumn();
                Square* adj = board -> getSquare(adjI, adjJ);
                if(adj){
                    enableSight(adj, true);
                    enableControl(adj, piecesSeen == 0);
                    if(adj -> piece()){
                        if(adj -> piece() -> getColor() != getColor()){
                            King* k = static_cast<King*>(getPlayer() -> getKing());
                            bool movePermission = k -> requestPermission(getSquare(), adj);
                            enableMove(adj, piecesSeen == 0 && movePermission);
                        }
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
}
    //std::cout << "Calibration success." << std::endl;