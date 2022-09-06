PROGRAMS = ./tictactoe
SCRIPTS  = ./tictactui
HEADERS  = board.h generic.h minimax.h
PREFIX   =/usr/local
CC       =cc
CFLAGS   =-g -Wall

all: $(PROGRAMS)
clean:
	rm -f $(PROGRAMS)
install:
	install -d                  $(DESTDIR)$(PREFIX)/bin
	install -m755 $(PROGRAMS)   $(DESTDIR)$(PREFIX)/bin
	install -m755 $(SCRIPTS)    $(DESTDIR)$(PREFIX)/bin
	install -d                  $(DESTDIR)$(PREFIX)/include/tictactui
	install -m644 $(HEADERS)    $(DESTDIR)$(PREFIX)/include/tictactui

./tictactoe: tictactoe.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<
## -- license --
ifneq ($(PREFIX),)
install: install-license
install-license: LICENSE
	@echo 'I share/doc/c-tictactui/LICENSE'
	@mkdir -p $(DESTDIR)$(PREFIX)/share/doc/c-tictactui
	@cp LICENSE $(DESTDIR)$(PREFIX)/share/doc/c-tictactui
endif
## -- license --
