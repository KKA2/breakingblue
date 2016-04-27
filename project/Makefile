CC=g++
CXXFLAGS=-g -Wall --std=c++11
LFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

MAIN=main.o
FUNC=Master.o Texture.o Person.o Player.o Enemy.o Sound.o Text.o
LEVELS=Levels.o Level.o Transition.o Level1.o Level2.o Level3.o Level4.o Intro.o

ALL=$(MAIN) $(FUNC) $(LEVELS)

all: main

main: $(ALL)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LFLAGS)

%.o: %.c
	$(CC) -c $(CXXFLAGS) -o %@ @^

clean:
	rm -rf *.o main *.dSYM &>/dev/null
