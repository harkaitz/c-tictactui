#ifndef BOARD_H
#define BOARD_H

#ifndef _POSIX_C_SOURCE
#  ifdef FLYCHECK
#    define _POSIX_C_SOURCE 201000L
#  else
#    error Please define _POSIX_C_SOURCE for strtok_r,ssize_t
#  endif
#endif

#include "generic.h"
#include "trim.h" /* Copied from "c-trim" project. */
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <syslog.h>

struct board_s {
    char    turn;
    char    winner;
    char    players[10];
    int     values[10];
    char    pieces[8][8];
    ssize_t X;
    ssize_t Y;    
};


static inline bool
board_read(struct meta_s *_m, struct board_s *_b, struct mem_s *_mm, FILE *_in)
{

    char          *body            = NULL;
    char *l;
    
    memset(_b, 0, sizeof(struct board_s));
    _mm->bsz = 0;
    
    
    while (_mm->bsz < sizeof(_mm->b)) {

        if (!(l = fgets(_mm->b + _mm->bsz, sizeof(_mm->b) - _mm->bsz, _in))) {
            return false;
        }
        _mm->bsz += strlen(l);
        
        if (l[0]=='.') {
            l[0] = '\0';
            break;
        }

        if (l[0]=='%' && l[1] == '\n') {
            body = l + strlen(l);
            l[0] = '\0';
            continue;
        }
    }

    if (body) {
        char *k,*v,*k_;
        for (k = strtok_r(_mm->b, "\n", &k_);
             k;
             k = strtok_r(NULL, "\n", &k_)) {

            if (!(v = strchr(k, ':'))) continue;
            *(v++) = '\0';
            
            if      (!strcmp(k, "turn"))   _b->turn = *trim(v);
            else if (!strcmp(k, "move"))   _m->moves[_m->movesz++] = trim(v);
            else if (!strcmp(k, "winner")) _b->winner = *trim(v);
            
        }
    } else {
        body = _mm->b;
    }
    

    ssize_t y = 0, x = 0;
    for (char *c = body; *c; c++) {
        if (*c == '|' && x<8 && y<8) {
            if (*(c+1)=='\n') {
                y++;
                if (x > _b->X) _b->X = x;
                x=0;
                c++;
            } else if (*(c+1)) {
                _b->pieces[x++][y] = *(c+1);
                c++;
            }
        }
    }
    _b->Y = y;

    for (x=0; x<_b->X; x++)
        for (y=0; y<_b->Y; y++)
            if (!_b->pieces[x][y])
                _b->pieces[x][y] = ' ';
    
    
    return true;
}

static inline void
meta_write(const struct meta_s *_m, FILE *_out, bool _print_moves)
{
    if (_print_moves) {
        for (size_t i=0; i<_m->movesz; i++) {
            fprintf(_out, "move: %s\n", _m->moves[i]);
        }
    }
}

static inline void
board_write(const struct board_s *_b, FILE *_out)
{
    int x, y;
    if (_b->winner) {
        fprintf(_out, "winner: %c\n", _b->winner);
    } else if (_b->turn) {
        fprintf(_out, "turn: %c\n", _b->turn);
    }
    if (_b->players[0]) {
        fprintf(_out, "players: %s\n", _b->players);
        fprintf(_out, "values:");
        for (int i=0; _b->players[i]; i++) {
            fprintf(_out, "%s%i", (i==0)?" ":",", _b->values[i]);
        }
        fprintf(_out, "\n");
    }
    
    fputs("%\n", _out);
    for (y=-1; y<_b->Y; y++) {
        fprintf(_out, "%1c", (y==-1)?' ':'a'+y);
        for (x=0; x<_b->X; x++) {
            if (y==-1) {
                fprintf(_out, " %c", '1'+x);
            } else {
                fprintf(_out, "|%c", _b->pieces[x][y]);
            }
        }
        fprintf(_out, "%c\n", (y==-1)?' ':'|');
    }
    fputs(".\n", _out);
}

static inline void
move_getnum(char c, ssize_t *_x, ssize_t *_y)
{
    if (c >= 'a' && c <= 'z') {
        *_y = c - 'a';
    } else if (c >= '1' && c <= '9') {
        *_x = c - '1';
    }
}

static inline int
board_value(const struct board_s *_b, char _pl)
{
    for (int i=0; _b->players[i]; i++) {
        if (_b->players[i]==_pl) {
            return _b->values[i];
        }
    }
    return 0;
}

static inline char
board_turn(const struct board_s *_b)
{
    return _b->turn;
}

static inline bool
move_add_link(struct meta_s *_m, char *move)
{
    if (_m->movesz<64) {
        _m->moves[_m->movesz++] = move;
        return true;
    } else {
        return false;
    }
}


#endif
