//
//  King.cpp
//  chess
//
//  Created by User on 2015-11-25.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#include "King.h"
#include <cmath>
King::King(char c) : Piece(c) {
    
    
       
    
}

double King::getMaterialValue() const{
    return 0.0;
}

void King::calibrate(){
    printCalibration();
    bool notInCheck = !(board -> isControlledByEnemiesOf(this, sq));

    if(board){
        
        for(int d = 0; d < 2; d++)
        for(int i = 0; i < 4; i++){
            int newI = Chess::ALL_DIRS[d][i][0] + sq -> getRow();
            int newJ = Chess::ALL_DIRS[d][i][1] + sq -> getColumn();
            
            Square* adj = board -> getSquare(newI, newJ);
            if(adj){
                //std::cout << "CALIBRATION (" << getPieceID() << ") AT: " << *adj << std::endl;
                enableSight(adj, true);
                enableControl(adj, true);
                Piece* piece = adj->piece();
                bool isEnemy = piece && (piece->getColor() != getColor());
                bool enemyCtrled = (board -> isControlledByEnemiesOf(this, adj));
                
                bool validMove = (isEnemy && !enemyCtrled) || (!piece && !enemyCtrled);
                
                //std::cout << BOLDMAGENTA << getPieceID() << " can" << (validMove ? "" : "\'t") << " move to " << *adj << RESET << std::endl;
                enableMove(adj, validMove);
            }
            
        }

        //CASTLING:
        if(!hasMoved() && notInCheck){
            int row = getSquare() -> getRow();
            int col = getSquare() -> getColumn();
            bool castleLeft = true;
            bool castleRight = true;
            
            Square* lsq = board -> getSquare(row, col - 4);
            Square* rsq = board -> getSquare(row, col + 3);
    
            Piece* lp = lsq ? lsq -> piece() : NULL;
            Piece* rp = rsq ? rsq -> piece() : NULL;
            
            if(lp && ((lp -> getPieceID() == 'r' || lp -> getPieceID() == 'R') && !(lp->hasMoved()))){
                //std::cout << "Left rook in place, hasn't moved." << std::endl;
                if(lp -> getColor() == getColor()){ //ensure same colour
                    for(int i = col - 1; i > 0; i--){
                        Square* adj = board -> getSquare(row,i);
                        Piece* adjPiece = adj -> piece();
                        if(board -> isControlledByEnemiesOf(this, adj) || adjPiece){
                            //std::cout << "L: Intermediate square controlled by enemies." << std::endl;
                            //std::cout << "Can't castle left." << std::endl;
                            castleLeft = false;
                            break;
                        }
                    }
                }else{
                    castleLeft = false;
                }
            }else{
                castleLeft = false;
            }
            
            if(rp && ((rp -> getPieceID() == 'r' || rp -> getPieceID() == 'R') && !(rp->hasMoved()))){
               // std::cout << "Right rook in place, hasn't moved." << std::endl;
                if(rp -> getColor() == getColor()){ //ensure same colour
                    
                    for(int i = col + 1; i < 7; i++){
                        //std::cout << " ** Looking at " << *arrBoard[row][i] << "\n";
                        Square* adj = board -> getSquare(row, i);
                        Piece* adjPiece = adj -> piece();
                        if(board -> isControlledByEnemiesOf(this, adj) || adjPiece){
                            /*if(board -> isControlledByEnemiesOf(this, adj))
                                //std::cout << "R: Intermediate square controlled by enemies." << std::endl;
                            if(board -> getSquare(row, i) -> piece())
                               // std::cout << "There's a piece in the way of castling.";
                            
                            //std::cout << "Can't castle right." << std::endl;*/
                            castleRight = false;
                            break;
                        }
                        //std::cout << " ^^^ No pieces control that square. Don't believe it? Here's the info: \n";
                        board -> getSquare(row, i) -> printInfoTo(std::cout);
                    }
                }else{
                    castleRight = false;
                }
            }else{
                castleRight = false;
            }
            Square* lDest = board -> getSquare(row, col-2);
            Square* rDest = board -> getSquare(row, col+2);
            enableMove(lDest, castleLeft);
            enableMove(rDest, castleRight);
        }
        
    }
   // std::cout << "Calibration success." << std::endl;
}

bool King::requestPermission(Square* from, Square* to){
    
    //we need to check first if the piece is pinned
    //then we need ensure piece blocks ALL pieces giving checks
    
    //need to check for pins because the piece giving the pin does not control
    //the king but has sight of it, in order to correctly ensure that all pieces checking the
    //king are blocked, we need to make sure that all pinned pieces stay in line with their pinners
    
    //std::cout << " ~~~ Permission Request: from " << *from << " to " << *to << " ~~~ " << endl;
    
    std::set<Square*>* fromControllers = board -> enemyControllersOf(this, from);
    
    set<Square*>::iterator fromIt;
    bool permission = true;
    //is the piece pinned?
    
    
    for(fromIt = fromControllers -> begin(); permission && fromIt != fromControllers -> end(); ++fromIt){
       // cout << "\t Consider controller on " << *fromIt << "\n";
        Square* kingSquare = sq;
        bool kingInSight = (*fromIt) -> piece() -> hasSight(kingSquare);
        //cout << "\t" << **fromIt << " has its enemy's king in sight.\n";
        
        bool pinned = kingInSight && inLine(kingSquare, from, *fromIt);
        //since the enemy can see the king, if the enemy is in line with this
        //and the king it MUST be the case that the piece requesting permission
        //is pinned, i.e, blocking check.
        if(pinned){ //cout << "\t\tThe controller on " << **fromIt << " is pinning " << *from << " on a line.\n";
            permission = inLine(kingSquare, to, *fromIt);
            //cout << "\t\tThe move does " << (permission ? "" : " NOT ") << "block check." << endl;
        }else{
            //cout << "\t\tThe piece is not pinned. Now depends on check.\n";
        }
    }
    
    fromControllers -> clear();
    delete fromControllers;

        //need to also make sure that the piece is blocking ALL of the checks.
    if(permission){
        std::set<Square*>* controllers = board -> enemyControllersOf(this, sq);
        set<Square*>::iterator attacker;
        for(attacker = controllers -> begin(); permission && attacker != controllers -> end(); ++attacker){
            //cout << "\t\t ** There is a check coming from " << **attacker <<".\n";
            permission = inLine(sq, to, *attacker);
            if(permission){
                //cout << "\t\t\tBut this move blocks that check.\n";
            }else{
               // cout << "\t\t\tAnd this move doesn't block the check, so INVALID.\n";
            }
        }
        controllers -> clear();
        delete controllers;
    }
    
    return permission;
}

bool King::inLine(Square* king, Square* defender, Square* attacker) const{
    
    if(defender == attacker)
        return true;
    
    int aR = attacker -> getRow();
    int aC = attacker -> getColumn();
    int dR = defender -> getRow();
    int dC = defender -> getColumn();
    int kR = king -> getRow();
    int kC = king -> getColumn();
    
    bool inLineRow = ( (aR <= dR && dR < kR) || (aR >= dR && dR >= kR) );
    bool inLineCol = ( (aC <= dC && dC < kR) || (aC >= dC && dC >= kC) );
    if( !inLineRow || !inLineCol ){
        return false;
    }
    
    //vector form king to defender should equal vec from defended to attacker
    
    double daR = dR - aR;
    double daC = dC - aC;
    double mag = std::sqrt(daR * daR + daC * daC);
    daR = (daR == 0 ? 0 : daR/mag);
    daC = (daC == 0 ? 0 : daC/mag);
    
    
    
   // cout << "\t\t*** Unit Vector a -> d = <" << daR << "," << daC <<">\n";
    
    
    
    double kaR = kR - aR;
    double kaC = kC - aC;
    double mag2 = std::sqrt(kaR * kaR + daC * daC);
    kaR = (kaR == 0 ? 0 : kaR/mag2);
    kaC = (kaC == 0 ? 0 : kaC/mag2);
    
   // cout << "\t\t*** Vector a -> k = <" << kaR << "," << kaC <<">\n";
    
    bool rowVecAligned = (daR == kaR);
    bool colVecAligned = (daC == kaC);
    
    return ( rowVecAligned && colVecAligned );

}

