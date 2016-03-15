CC=g++
CFLAGS=-w
LFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
MAIN=tutorial

all: $(MAIN)

$(MAIN): $(MAIN).o Master.o Texture.o Person.o Sound.o
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o %@ @^

clean:
	rm *.o $(MAIN) &>/dev/null
