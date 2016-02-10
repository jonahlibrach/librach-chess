///
        //  Pawn.cpp
        //  chess
        //
        //  Created by User on 2015-11-25.
        //  Copyright (c) 2015 Jonah Librach. All rights reserved.
        //
        
#include "Pawn.h"
        
Pawn::Pawn(char c) : Piece(c) {}
        
Pawn::~Pawn(){}
        
double Pawn::getMaterialValue() const{
    return 1.0;
}
        
void Pawn::calibrate(){
    if(!player)
        return;
    
    printCalibration();
    int dir = getColor() ? 1 : -1;
    int bottom = 7 * getColor() - dir * 7;
    King* k = static_cast<King*>(getPlayer() -> getKing());
    bool movePermission;
    Square* adj;
    
    if(board){
        if(bottom == sq -> getRow() - dir){
                //cout << "\tThis pawn is at its initial position!\n";
            adj = board -> getSquare(sq -> getRow() + 1 * dir, sq -> getColumn());
            
            //cout << "Potential adj is " << *adj << endl;
            
            if(adj && !(adj -> piece())){
                adj = board -> getSquare(sq -> getRow() + 2 * dir, sq -> getColumn());
                
                if(adj && !(adj -> piece())){
                    movePermission = k -> requestPermission(sq, adj);
                    if(movePermission){
                        //cout << "Granted permission to move " << *sq << " to " << *adj << "\n";
                        enableMove(adj, movePermission);}
                }
            }
        }
        
        adj = board -> getSquare(sq -> getRow() + dir, sq -> getColumn());
    
        if(adj && !(adj -> piece())){
            movePermission = k -> requestPermission(sq, adj);
            if(movePermission){
                //cout << "Granted permission to move " << *sq << " to " << *adj << "\n";
                enableMove(adj, movePermission);}
        }
                
                //END OF REG PAWN MOVEMENT
                
                //PAWN CAPTURES
        
        Square* captures[2]  = { board -> getSquare(sq -> getRow() + dir, sq -> getColumn() - 1),
                                board -> getSquare(sq -> getRow() + dir, sq -> getColumn() + 1) };
        
        for(int i = 0; i < 2; i++){
            if(captures[i]){
                enableControl(captures[i], true);
                Piece* cap = captures[i] -> piece();
                if(cap && cap -> getColor() != getColor()){
                    movePermission = k -> requestPermission(sq, captures[i]);
                        //cout << "Granted permission to move " << *sq << " to " << *adj << "\n";
                    enableMove(captures[i], movePermission);
                }
            }
        }//end of capture loop
    }
    
}
