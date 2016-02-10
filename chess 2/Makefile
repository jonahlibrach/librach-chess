XX = g++
CXXFLAGS = -Wall -MMD -g
EXEC = chess
PIECES = 
OBJECTS = main.o Game.o Board.o Square.o  Piece.o King.o Queen.o Rook.o Bishop.o Knight.o Pawn.o Move.o Player.o Human.o AI.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS} 
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${DEPENDS}
