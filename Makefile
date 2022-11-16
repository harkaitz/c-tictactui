PROGRAMS = ./tictactoe
SCRIPTS  = ./tictactui
HEADERS  = board.h generic.h minimax.h
PREFIX   =/usr/local
CC       =cc
CFLAGS   =-g -Wall

all: $(PROGRAMS)
clean:
	@echo "D $(PROGRAMS)"
	@rm -f $(PROGRAMS)
install:
	@echo "I bin/ $(PROGRAMS) $(SCRIPTS)"
	@install -d                  $(DESTDIR)$(PREFIX)/bin
	@install -m755 $(PROGRAMS)   $(DESTDIR)$(PREFIX)/bin
	@install -m755 $(SCRIPTS)    $(DESTDIR)$(PREFIX)/bin
	@echo "I include/tictactui/ $(HEADERS)"
	@install -d                  $(DESTDIR)$(PREFIX)/include/tictactui
	@install -m644 $(HEADERS)    $(DESTDIR)$(PREFIX)/include/tictactui

./tictactoe: tictactoe.c $(HEADERS)
	@echo "B $@ $^"
	@$(CC) $(CFLAGS) -o $@ $<
## -- license --
install: install-license
install-license: LICENSE
	@echo 'I share/doc/c-tictactui/LICENSE'
	@mkdir -p $(DESTDIR)$(PREFIX)/share/doc/c-tictactui
	@cp LICENSE $(DESTDIR)$(PREFIX)/share/doc/c-tictactui
## -- license --
