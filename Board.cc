//
//  Board.cc
//  chess
//
//  Created by User on 2015-11-23.
//  Copyright (c) 2015 Jonah Librach. All rights reserved.
//

#include "Board.h"
#define GREY_BG "\033[47m"

/*
Reads a board structure file and two integers, row and column for the first line of the file.
At the beginning of each line is one char that represents the rank (i.e, the row)
The last line consists of a space and then characters which represent the files.

*/

Board::~Board(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            delete board[i][j];
        }
        delete [] board[i];
    }
    delete [] board;
}

bool Board::isControlledByEnemiesOf(Piece* p, Square* s) const{
    
    std::set<Square*>* controllers = s -> getControllers();
    std::set<Square*>::iterator it;
    
    for(it = controllers -> begin(); it != controllers-> end(); ++it){
        Piece* potentialEnemy = (*it) -> piece();
        if(potentialEnemy->getColor() != p -> getColor())
            return true;
    }
    return false;
}

std::set<Square*>* Board::enemyControllersOf(Piece* p, Square* s) const{
    
    set<Square*>* eConts = new set<Square*>;
    set<Square*>::iterator it = s -> getControllers() -> begin();
    for( ; it != s->getControllers()->end(); ++it){
        Piece* potentialEnemy = (*it) -> piece();
        if(potentialEnemy->getColor() != p -> getColor())
            eConts -> insert(*it);
        
    }
    return eConts;
}

void Board::setupBoardStructure(std::string& file){

    //std::cout << "setupBoard(): initializing: " << file << std::endl;
    std::ifstream stream(file);
    //std::cout << "created and opened input file stream." << std::endl;

    stream >> rows;
    stream >> cols;
    if(stream.fail()){
        std::cout << "Stream failed." << std::endl;
    }
    std::cout << rows << " " << cols << std::endl;
    rowMap = new std::map<char, int>;
    board = new Square**[rows];
    
    for(int i = 0; i < rows; i++){
        
        char c;
        stream >> c;
        board[i] = new Square*[cols];
        //std::cout << c << " will map to: " << i << std::endl;
        (*rowMap)[c] = i;
        
        
        
        for(int j = 0; j < cols; j++){
            char boardChar;
            stream >> boardChar;
            //std::cout << "board char is: \'" << boardChar << "\'" << std::endl;
            if(boardChar == '_'){
               // std::cout << "Creating square at: " << i << "," << j << std::endl;
                board[i][j] = new Square(i, j);
            }else{
               // std::cout << "Setting " << i << "," << j << " to NULL." << std::endl;
                board[i][j] = NULL;
            }
        }
    }
    
    stream.ignore();
    columnMap = new std::map<char, int>;
    for(int i = 0; i < cols; i++){
        
        char c;
        stream >> c;
        //std::cout << c << " will map to: " << i << std::endl;
        (*columnMap)[c] = i;
        
    }
}

int Board::getRows() const{
    return rows;
}

int Board::getColumns() const{
    return cols;
}

bool*** Board::getBoolEquivalent(){
    
    if(board == NULL)
        return NULL;
    
    bool*** bitboard = new bool**[rows];
    for(int i = 0; i < rows; i++){
        bitboard[i] = new bool*[cols];
        for(int j = 0; j < cols; j++){
            if(board[i][j] != NULL){
                bitboard[i][j] = new bool;
                *bitboard[i][j] = false;
            }else{
                bitboard[i][j] = NULL;
            }
        }
    }
    
return bitboard;
}

Board::Board(std::string& boardStructureFile){
    board = NULL;
    rowMap = NULL;
    columnMap = NULL;
    pieceSet = NULL;
    settingUp = false;
    
    setupBoardStructure(boardStructureFile);
    
}

Square* Board::getSquare(int row, int col) const{
    if(row < 0 || row >= rows || col < 0 || col >= cols)
        return NULL;
    return board[row][col];
}

Square* Board::getSquare(std::string squareID) const{
   // std::cout << "Getting square: " << squareID << std::endl;
    
    int rowQ = -1, colQ = -1;
    
    if(squareID.length() != 2)
        return NULL;
    
    if(rowMap -> find(squareID[1]) != rowMap -> end()){
        rowQ = rowMap -> find(squareID[1]) -> second;
    }
    
    if(columnMap -> find(squareID[0]) != columnMap -> end()){
        colQ = columnMap -> find(squareID[0]) -> second;
    }
    
    //std::cout << "Square found was ROW: " << rowQ << ", COL: " << colQ << std::endl;
    return (rowQ != -1 && colQ != -1) ? getSquare(rowQ, colQ) : NULL;
    
}

void printUnicodeBoardTo(std::ostream& out){
    
}

void Board::printTo(std::ostream& out) const{
    
   // printUnicodeBoardTo(out);

    for(int i = 0; i < 8; i++){
        out << (char)('8' - i) << ' ';
        for(int j = 0; j < 8; j++){
            cout << ((i%2 ^ j%2) ? GREY_BG : RESET);
            Piece* p = board[i][j] -> piece();
            if(p){
                cout << p -> unicode();
            }else{
                cout << " ";
            }
            
        }
        out << RESET << endl;
    }
    
    /*for(int i = 0; i < rows; i++){
        
        for(int j = 0; j < cols; j++){
            
            if (c == '_'){
                if ((i%2 == 1 && j%2 == 1) || ((i%2 == 0) && (j%2 == 0))){
                    c = ' ';
                }
            }
            
            out << c;
        }
        out << "\n";
    }*/
    out << "  abcdefgh"<< "\n";
}

int Board::initSetup(istream& in, std::string& gameState, Piece* (pieceFactory)(char), PieceSet* pieceSet){
    
    
    //std::cout << "initSetup" << std::endl;
    this -> pieceSet = pieceSet;
    settingUp = true;
    std::ifstream positionReader(gameState);
    int turn = 0;
    //read the board in with the nested for-loop
    for(int i = 0; i < rows; i++){
        std::string readRank;
        getline(positionReader, readRank);
        for(int j = 0; j < cols; j++){
            char c = readRank[j];
            if(c != '_'){
                Piece* piece = pieceFactory(c);
                if(piece){
                    replacePiece(getSquare(i, j), piece);
                    notifyChange(getSquare(i,j));
                }
            }
        }
    }
    printTo(cout);
    std::map<char,int>::iterator it;
   /* for(it = pieceCount -> begin(); it != pieceCount->end(); ++it){
        std::cout << "("<<it->first<<","<<it->second<<")"<<std::endl;
    }*/
    
    char toPlay;
    positionReader >> toPlay;
    if(toPlay == 'B')
        turn = 1;
    else
        turn = 0;

    //std::cout << "initSetup success." << std::endl
    
    string command;
    while(true){
        
        in >> command;
        if(command == "done"){
            
            if((*pieceSet)['K'].size() ==  1 && (*pieceSet)['k'].size() ==  1){
                std::cout << (turn ? "Black" : "White") << " to play." << std::endl;
                return turn;
            }else{
                std::cout << "Illegal number of kings on the board." << std::endl;
            }
        
        }
        
        else if(command == "+"){
            char piece;
            in >> piece;
            string placement;
            in >> placement;
            Piece* toAdd = pieceFactory(piece);
            if(toAdd){
                replacePiece(getSquare(placement), pieceFactory(piece));
            }else{
                cout << "Illegal setup command.\n";
            }
        }else if(command == "-"){
            string loc;
            in >> loc;
            Square* sq = getSquare(loc);
            if(sq){
                replacePiece(getSquare(loc), NULL);
            }else{
                cout << "Illegal setup command.\n";
            }
        }else if(command == "="){
            string whoGoes;
            in >> whoGoes;
            if(whoGoes == "white")
                turn = 0;
            else if(whoGoes == "black")
                turn = 1;
            else{
                cout << "Illegal setup command.\n";
            }
        }else{
            cout << "Illegal setup command." << endl;
            continue;
        }
        printTo(cout);
        
    }

    
    
    
}

char Board::squareChar(Square* s) const{
    if(s -> piece())
        return (s -> piece() -> getPieceID());
    else
        return ' ';
}

Piece* Board::replacePiece(Square* sq, Piece* p){
    
    if(!sq){
        std::cout << "Cannot process a NULL square for replacePiece()." << std::endl;
        return NULL;
    }
    if(p){
        ((*pieceSet)[p->getPieceID()]).insert(p);
    }
    
    //set the piece on the board and get the piece that was there, null if nothing was
    
    Piece* prev = sq -> setPiece(p);
    if(p){
        p -> setBoard(this);
        p -> setSquare(sq);
        p -> calibrate();
    }
    
    if(prev){
       // std::cout << "::Board, Removing connection of previous piece to the game." << std::endl;
        prev -> reset();
        //std::cout << "The amount of " << prev -> getPieceID() << " was " << (*pieceSet)[prev -> getPieceID()].size() << "\n";
       // std::cout << "Erasing " << prev << "\n";
        (*pieceSet)[prev -> getPieceID()].erase(prev);
       // std::cout << "The amount of " << prev -> getPieceID() << " is now " << (*pieceSet)[prev -> getPieceID()].size() << "\n";
       //std::cout << "Piece disconnection success." << std::endl;
    }
   
    //this MUST be AFTER the piece sets its board to this
   // std::cout << "Piece replacement success." << std::endl;
    return prev;
}

void Board::notifyChange(Square* sq){
   // std::cout << "----> Notify Change: " << *sq << std::endl;
    std::list<Piece*> toNotify;
    int r = sq -> getRow();
    int c = sq -> getColumn();
   // std::cout << "Notifying in-line square " << *sq << std::endl;
    for(int d = 0; d < 2; d++)
    for(int i = 0; i < 4; i++){
        for(int j = 1; j <= 8; j++){
            Square* newSq = getSquare(Chess::ALL_DIRS[d][i][0] * j + r, Chess::ALL_DIRS[d][i][1] * j + c);
            
            //if(newSq){ std::cout << "Examining " << *newSq << std::endl; }
            
            if(newSq && newSq -> piece()){
               // std::cout << "Pushed " << *newSq << std::endl;
                toNotify.push_front(newSq -> piece());
            }
        }
    }
    
    for(int i = 0; i < 8; i++){
        Square* toRecal = getSquare(Chess::KNIGHT[i][0] + r, Chess::KNIGHT[i][1] + c);
        if(toRecal)
            //std::cout << BLUE << "Looking at " << *toRecal << RESET "\n";
        if(toRecal && toRecal -> piece())
            toNotify.push_front(toRecal -> piece());
    }
    std::list<Piece*>::iterator it;
    //std::cout << "Going from BEGIN to END\n";
    for(it = toNotify.begin(); it != toNotify.end(); ++it){
        (*it) -> reset();
        (*it) -> calibrate();
    }
    //std::cout << "Going from END to BEGIN\n";
    std::list<Piece*>::reverse_iterator rit;
    for(rit = toNotify.rbegin(); rit != toNotify.rend(); ++rit){
        
        (*rit) -> reset();
        (*rit) -> calibrate();
    }
    
    //std::cout << "End of change notification." << std::endl;

}

Piece* Board::findPiece(char c) const{
    
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(board[i][j] && board[i][j] -> piece() && board[i][j] -> piece() -> getPieceID() == c)
                return board[i][j] -> piece();
        }
    }
    return NULL;
    
}