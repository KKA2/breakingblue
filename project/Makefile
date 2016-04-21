CC=g++
CXXFLAGS=-w
LFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
ALL=main.o Master.o Texture.o Person.o Sound.o Levels.o Level.o Level1.o

all: main

main: $(ALL)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LFLAGS)

%.o: %.c
	$(CC) -c $(CXXFLAGS) -o %@ @^

clean:
	rm *.o main &>/dev/null
