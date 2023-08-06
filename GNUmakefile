PROJECT  =c-tictactui
VERSION  =1.0.0
PROGRAMS =./tictactoe
SCRIPTS  =./tictactui
HEADERS  = board.h generic.h minimax.h
PREFIX   =/usr/local
CC       =cc
CFLAGS   =-g -Wall
## -- targets
all: $(PROGRAMS)
clean:
	rm -f $(PROGRAMS)
install:
	install -d                  $(DESTDIR)$(PREFIX)/bin
	install -m755 $(PROGRAMS)   $(DESTDIR)$(PREFIX)/bin
	install -m755 $(SCRIPTS)    $(DESTDIR)$(PREFIX)/bin
	install -d                  $(DESTDIR)$(PREFIX)/include/tictactui
	install -m644 $(HEADERS)    $(DESTDIR)$(PREFIX)/include/tictactui
## -- program
./tictactoe: tictactoe.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<
## -- BLOCK:license --
install: install-license
install-license: 
	mkdir -p $(DESTDIR)$(PREFIX)/share/doc/$(PROJECT)
	cp LICENSE README.md $(DESTDIR)$(PREFIX)/share/doc/$(PROJECT)
update: update-license
update-license:
	ssnip README.md
## -- BLOCK:license --
## -- BLOCK:man --
## -- BLOCK:man --
