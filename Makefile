GCC=g++
SRC_MAIN=monopoly
SRC_INTER=interaction
SRC_OUTIL=outils
SRC_TRAIT=traitement
SRC_SDL=sdl
SRC_INIT=initialisation

ALL_SRC=$(SRC_SDL).o $(SRC_INTER).o $(SRC_OUTIL).o $(SRC_TRAIT).o $(SRC_INIT).o $(SRC_MAIN).o

OPTIONS=-w -W -Wall -O3 -g3 #-lm -pedantic -ansi

CFLAGS=`sdl-config --cflags`
LIBS=`sdl-config --libs` -lSDL_ttf -lSDL_gfx -lSDL_image

all:$(ALL_SRC) $(SRC_MAIN)

$(SRC_SDL).o:$(SRC_SDL)/$(SRC_SDL).c
	$(GCC) $(OPTIONS) $(CFLAGS) -c $^
	
$(SRC_INTER).o:$(SRC_INTER)/$(SRC_INTER).c
	$(GCC) $(OPTIONS) $(CFLAGS) -c $^

$(SRC_INIT).o:$(SRC_INIT)/$(SRC_INIT).c
	$(GCC) $(OPTIONS) $(CFLAGS) -c $^

$(SRC_OUTIL).o:$(SRC_OUTIL)/$(SRC_OUTIL).c
	$(GCC) $(OPTIONS) $(CFLAGS) -c $^

$(SRC_TRAIT).o:$(SRC_TRAIT)/$(SRC_TRAIT).c
	$(GCC) $(OPTIONS) $(CFLAGS) -c $^

$(SRC_MAIN).o:$(SRC_MAIN).c
	$(GCC) $(OPTIONS) $(CFLAGS) -c $^


$(SRC_MAIN):$(ALL_SRC)
	$(GCC) $(OPTIONS) $(LIBS) $(ALL_SRC) -o $(SRC_MAIN)
	
clean:
	rm -f *.o *~
