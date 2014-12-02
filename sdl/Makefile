CC=gcc
PRGM=$(SRC:.c=)
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
OPTIONS=-Wall -O2 -g3 -lm
CFLAGS=`sdl-config --cflags`
LIBS=`sdl-config --libs` -lSDL_ttf -lSDL_gfx

all:$(PRGM)

$(PRGM):$(OBJ)
	$(CC) $(OPTIONS) $(LIBS) $^ -o $@
	make clean

%.o:%.c
	$(CC) $(OPTIONS) -c $(CFLAGS) $^

clean:
	rm -f *.o *~
