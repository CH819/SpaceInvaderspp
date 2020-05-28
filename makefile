IDIR = include
CC = g++
CFLAGS = -I$(IDIR) -lncurses

SDIR = src

_DEPS = alien.h game.h projectile.h ship.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_SRC = main.cpp alien.cpp game.cpp projectile.cpp ship.cpp
SRC = $(patsubst %,$(SDIR)/%,$(_SRC))

play: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
