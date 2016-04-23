CC=g++
CXXFLAGS=-g -Wall --std=c++11
LFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
ALL=main.o Master.o Texture.o Person.o Player.o Sound.o Levels.o Level.o Level1.o Level2.o Text.o

all: main

main: $(ALL)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LFLAGS)

%.o: %.c
	$(CC) -c $(CXXFLAGS) -o %@ @^

clean:
	rm -rf *.o main *.dSYM &>/dev/null
