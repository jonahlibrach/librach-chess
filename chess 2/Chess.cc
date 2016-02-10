#include "Chess.h"

namespace Chess{
    
    const char MAPPING[] = {'a','b','c','d','e','f','g','h'};
    
    int DIAGONAL[4][2] = {{1,1},{1,-1},{-1,-1},{-1,1}};
    int ADJACENT[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
    int KNIGHT_MOVES[8][2] = {{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},
        {-1,2},{-1,-2}};
    int KING_MOVES[8][2] = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
    
    
    
    
}


Piece* Chess::pieceFactory(char c){
    
   /* if(c == 'p' || c == 'P'){
        return new Pawn(c);
    }else if(c == 'n' || c == 'N'){
        return new Knight(c);
    }else if(c == 'b' || c == 'B'){
        return new Bishop(c);
    }else if(c == 'r' || c == 'R'){
        return new Rook(c);
    }else if(c == 'q' || c == 'Q'){
        return new Queen(c);
    }else*/
        
    if(c == 'k' || c == 'K'){
        return new King(c);
    }
    
    return NULL;
}

