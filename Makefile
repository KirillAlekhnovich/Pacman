CXX=g++
LD=g++
CXXFLAGS=-Wall -pedantic
PROGRAM=Pacman


all: deps compile

compile: $(PROGRAM)

run:
	./$(PROGRAM)

Pacman: ./src/App/CApp.o ./src/Game/CConfig.o ./src/Game/CGame.o ./src/Game/CGameOverMenu.o ./src/Game/CMainMenu.o ./src/GameMap/CMap.o ./src/GameMap/CScoreBoard.o ./src/Object/Sprite/Ghost/CBlue.o ./src/Object/Sprite/Ghost/CGhost.o ./src/Object/Sprite/Ghost/COrange.o ./src/Object/Sprite/Ghost/CPink.o ./src/Object/Sprite/Ghost/CRed.o ./src/Object/Sprite/Pacman/CPacman.o ./src/Object/Sprite/CMovingObject.o ./src/Object/CObject.o ./src/main.o
	$(LD) $(CXXFLAGS) -o $@ $^ -lSDL2 -lSDL2_image -lSDL2_ttf

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f ./src/*.o ./src/App/*.o ./src/Game/*.o ./src/GameMap/*.o ./src/Object/*.o ./src/Object/Sprite/*.o ./src/Object/Sprite/Ghost/*.o ./src/Object/Sprite/Pacman/*.o Makefile.d $(PROGRAM)

deps:
	$(CXX) -MM ./src/*.cpp ./src/App/*.cpp ./src/Game/*.cpp ./src/GameMap/*.cpp ./src/Object/*.cpp ./src/Object/Sprite/*.cpp ./src/Object/Sprite/Ghost/*.cpp ./src/Object/Sprite/Pacman/*.cpp > Makefile.d

-include Makefile.d
