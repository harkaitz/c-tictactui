PROJECT  =c-tictactui
VERSION  =1.0.0
PROGRAMS =./tictactoe
SCRIPTS  =./tictactui
HEADERS  = board.h generic.h minimax.h
PREFIX   =/usr/local
CC       =gcc -pedantic-errors -std=c99 -Wall
##
all: $(PROGRAMS)
clean:
	rm -f $(PROGRAMS)
install:
	@install -d $(DESTDIR)$(PREFIX)/bin
	@install -d $(DESTDIR)$(PREFIX)/include/tictactui
	install -m755 $(PROGRAMS) $(DESTDIR)$(PREFIX)/bin
	install -m755 $(SCRIPTS) $(DESTDIR)$(PREFIX)/bin
	install -m644 $(HEADERS) $(DESTDIR)$(PREFIX)/include/tictactui
./tictactoe$(EXE): tictactoe.c $(HEADERS)
	$(CC) -o $@ $< $(CFLAGS)
## -- BLOCK:license --
install: install-license
install-license: 
	@mkdir -p $(DESTDIR)$(PREFIX)/share/doc/$(PROJECT)
	cp LICENSE  $(DESTDIR)$(PREFIX)/share/doc/$(PROJECT)
## -- BLOCK:license --
