# TICTACTUI

A command line tui utility for TicTacToe (tictactoe.c) written
following the UNIX philosophy (pipe oriented etc) and a TUI
interface (tictactui) in SH language.

Features:

- A simple generic minimax function: [minimax.h](./minimax.h).
- A reusable command line utility: [tictactoe.c](./tictactoe.c).
- A TUI (Text User Interface) game: [tictactui](./tictactui).

## Getting Started

Create a new game with (-g)

    > tictactoe -g
    turn: x
    players: xo
    values: 0,0
    %
      1 2 3
    a| | | |
    b| | | |
    c| | | |
    .

Pipe the new game to another tictactoe process that calculates a
good play with minimax (-i) and applies it (-a).

    > tictactoe -g | tictactoe -ia
    turn: o
    players: xo
    values: 0,0
    %
      1 2 3
    a|x| | |
    b| | | |
    c| | | |
    .

See all the moves in the second play.

    > tictactoe -g | tictactoe -ia | tictactoe -M
    move: a2
    move: a3
    move: b1
    move: b2
    move: b3
    move: c1
    move: c2
    move: c3
    turn: o
    players: xo
    values: 0,0
    %
      1 2 3 
    a|x| | |
    b| | | |
    c| | | |
    .

You can specify a move with "-m" and apply it with "-a".

    > tictactoe -g | tictactoe -ia | tictactoe -m c3 -a | tictactoe -ia
    turn: o
    players: xo
    values: 0,0
    %
      1 2 3
    a|x| |x|
    b| | | |
    c| | |o|
    .

And many more, read the help with "-h".

    > tictactoe -h

## Prerequisites

A POSIX C libc library and a C99 compiler is enough. For the TUI you
need a POSIX shell in /bin/sh.

## Installing

As always:

    make all
    sudo make install
    make clean

## Things to contribute

We need more games, how about chess?

## Collaborating

For making bug reports, feature requests and donations visit
one of the following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)

