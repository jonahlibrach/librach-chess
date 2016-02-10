CXX = g++
CXXFLAGS = -Wall -MMD -g
EXEC = a4q1
OBJECTS = main.o sorted.o unsorted.o vector.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${DEPENDS}