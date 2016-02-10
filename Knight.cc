//
//  Knight.cc
//  chess
//
//  Created by User on 2015-11-25.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#include "Knight.h"

Knight::Knight(char c) : Piece(c) {}

double Knight::getMaterialValue() const{
    return 3.0;
}

std::string Knight::unicode() const{
    return (getColor() ? "\u265E" : "\u2658");
}

void Knight::calibrate(){
    if(!player)
        return;
    printCalibration();
    // std::cout << "Starting Knight calibration." << std::endl;
    if(board){
        for(int i = 0; i < 8; i++){
            int adjI = Chess::KNIGHT[i][0] + sq -> getRow();
            int adjJ = Chess::KNIGHT[i][1] + sq -> getColumn();
            Square* adj = board -> getSquare(adjI, adjJ);
            if(adj){
                enableSight(adj, true);
                enableControl(adj, true);
                if((adj -> piece() && adj -> piece() -> getColor() != getColor()) || !(adj -> piece())){
                    //std::cout << "\tEnabling " << *adj << " for this knight." << std::endl;
                    King* k = static_cast<King*>(getPlayer() -> getKing());
                    bool movePermission = k -> requestPermission(getSquare(), adj);
                    enableMove(adj, movePermission);
                }
            }
    }
    //std::cout << "Calibration success." << std::endl;
    }
}