CXX = g++
CXXFLAGS = -std=c++20 -Wall -MMD -g3
EXEC1 = tetris
AGE = ./AGE
GAME1 = ./Tetris
SOURCES1 = $(wildcard $(AGE)/*.cc) $(wildcard $(GAME1)/*.cc)
OBJECTS1 = ${SOURCES1:.cc=.o}

EXEC2 = pacman
GAME2 = ./PacMan
SOURCES2 = $(wildcard $(AGE)/*.cc) $(wildcard $(GAME2)/*.cc)
OBJECTS2 = ${SOURCES2:.cc=.o}

DEPENDS = ${OBJECTS1:.o=.d} ${OBJECTS2:.o=.d} $(wildcard $(AGE)/*.h=.d) $(wildcard $(GAME1)/*.h=.d) $(wildcard $(GAME2)/*.h=.d) 
all: ${EXEC1} ${EXEC2}	

${EXEC1}: ${OBJECTS1}
	${CXX} ${OBJECTS1} ${GIVEN} -o ${EXEC1} ${CXXFLAGS} -lncursesw

${EXEC2}: ${OBJECTS2}
	${CXX} ${OBJECTS2} ${GIVEN} -o ${EXEC2} ${CXXFLAGS} -lncursesw

.PHONY: clean

clean:
	rm ${OBJECTS1} ${OBJECTS2} ${EXEC1} ${EXEC2} ${DEPENDS}