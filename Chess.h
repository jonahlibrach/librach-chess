//
//  Chess.h
//  chess
//
//  Created by User on 2015-11-25.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#ifndef chess_Chess_h
#define chess_Chess_h

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

namespace Chess{

    static  unsigned int const CAPTURE = 2, CHECK = 3, CHECKMATE = 5, EN_PASSENT = 7, PROMOTION = 11, CASTLE = 13;
    const char MAPPING[] = {'a','b','c','d','e','f','g','h'};
    static int const DIAGONAL[4][2] = {{1,1},{1,-1},{-1,-1},{-1,1}};
    static int const ADJACENT[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
    static int const KNIGHT[8][2] = {
        {-2,1}, {-1,2}, {1,2}, {2,1}, {2,-1}, {1,-2}, {-1,-2}, {-2,-1}
    };
    
    static int const ALL_DIRS[2][4][2] = { {{1,1},{1,-1},{-1,-1},{-1,1}} , {{1,0},{0,1},{-1,0},{0,-1}} };
    
    static char const LOCATION_VALUE[8][8] =
    {
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 1, 2, 2, 2, 2, 1, 0 },
        { 0, 1, 2, 3, 3, 2, 1, 0 },
        { 0, 1, 2, 3, 3, 2, 1, 0 },
        { 0, 1, 2, 2, 2, 2, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }, };
        
        
    
};

#endif
