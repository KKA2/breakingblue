CC=g++
CFLAGS=-w -g
LFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
ALL=main.o Master.o Texture.o Person.o Sound.o Levels.o Level1.o

all: main

main: $(ALL)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o %@ @^

clean:
	rm *.o main &>/dev/null
