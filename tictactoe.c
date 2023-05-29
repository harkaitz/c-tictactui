#define _POSIX_C_SOURCE 201000L
#define BOARD_TYPE struct board_s
#include "board.h"
#include "minimax.h"
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

#define COPYRIGHT_LINE \
    "Copyright (c) 2023 Harkaitz Agirre, harkaitz.aguirre@gmail.com" "\n" \
    ""

static char
tictactoe_winner_and_value(struct board_s *_b)
{
    size_t pos[8][3][2] = {
        
        { {0,0}, {0,1}, {0,2} },
        { {1,0}, {1,1}, {1,2} },
        { {2,0}, {2,1}, {2,2} },

        { {0,0}, {1,0}, {2,0} },
        { {0,1}, {1,1}, {2,1} },
        { {0,2}, {1,2}, {2,2} },

        { {0,0}, {1,1}, {2,2} },
        { {2,0}, {1,1}, {0,2} }
    };

    for (int p=0; p<8; p++) {
        char p1 = _b->pieces[pos[p][0][0]][pos[p][0][1]];
        char p2 = _b->pieces[pos[p][1][0]][pos[p][1][1]];
        char p3 = _b->pieces[pos[p][2][0]][pos[p][2][1]];
        if (p1 != ' ' && (p1 == p2) && (p2 == p3)) {
            _b->winner     = p1;
            _b->players[0] = 'x';
            _b->values[0]  = (p1=='x')?1:-1;
            _b->players[1] = 'o';
            _b->values[1]  = (p1=='o')?1:-1;
            return p1;
        }
    }
    int c = 0;
    for (int x=0; x<_b->X; x++)
        for (int y=0; y<_b->Y; y++)
            if (_b->pieces[x][y]==' ')
                c++;
    if (c==0) {
        _b->winner = 'n';
    }
    _b->players[0] = 'x';
    _b->values[0]  = 0;
    _b->players[1] = 'o';
    _b->values[1]  = 0;
    return '\0';
}

static void
tictactoe_moves(struct meta_s *_m, const struct board_s *_b)
{
    static struct {
        int   x,y;
        char *s;
    } moves[] = {
        {0,0,"a1"}, {1,0,"a2"}, {2,0,"a3"},
        {0,1,"b1"}, {1,1,"b2"}, {2,1,"b3"},
        {0,2,"c1"}, {1,2,"c2"}, {2,2,"c3"},
    };
    if (!_b->winner)
        for (int i=0; i<9; i++)
            if (_b->pieces[moves[i].x][moves[i].y]==' ')
                _m->moves[_m->movesz++] = moves[i].s;
}

static bool
tictactoe_apply(struct board_s *_b, const char *_mv) {
    ssize_t x = -1, y = -1;
    if (!_mv[0] || !_mv[1]/*err*/) return false;   
    move_getnum(_mv[0], &x, &y);
    move_getnum(_mv[1], &x, &y);
    if (x<0 || x>=_b->X || y<0 || y>=_b->Y/*err*/) return false;
    if (_b->pieces[x][y]!=' '/*err*/) return false;
    _b->pieces[x][y] = _b->turn;
    _b->turn = (_b->turn=='x')?'o':'x';
    return true;
}

static char const help[] =
    "Usage: tictactoe OPTS..."                             "\n"
    ""                                                     "\n"
    "The classic TicTacToe game that follows the UNIX"     "\n"
    "philosophy."                                          "\n"
    ""                                                     "\n"
    "-g      : Create a new game, instead of reading from" "\n"
    "          the standard input."                        "\n"
    "-m MOVE : Specify a move, ie 'a1'."                   "\n"
    "-M      : Specify all posible moves."                 "\n"
    "-i      : Select a move using the Minimax algorithm." "\n"
    "-a      : Apply the specified moves."                 "\n"
    ""                                                     "\n"
    COPYRIGHT_LINE;

static char const board[] =
    "turn: x"       "\n"
    "%"             "\n"
    "  1 2 3"       "\n"
    "a| | | |"      "\n"
    "b| | | |"      "\n"
    "c| | | |"      "\n"
    "."             "\n";

static struct minimax_s tictactoe_mx = {
    .bsz = sizeof(struct board_s),
    .get_turn = board_turn,
    .get_moves = tictactoe_moves,
    .get_winner_and_value = tictactoe_winner_and_value,
    .get_value = board_value,
    .apply_move = tictactoe_apply
};


int main (int _argc, char *_argv[]) {

    FILE          *in        = NULL;
    bool           o_apply   = false;
    bool           o_moves   = false;
    bool           o_minimax = false;
    int            ret       = 1;

    struct meta_s  m  = {0};
    struct board_s b1 = {0};
    struct board_s b2 = {0};
    struct mem_s   mm = {0};

    size_t         mv;
    int            opt;
    char           winner;
    
    while((opt = getopt (_argc, _argv, "hgm:aMi")) != -1) {
        switch (opt) {
        case 'h': fputs(help, stdout); return 0;
        case 'g': in = fmemopen((char*)board, sizeof(board)-1, "r"); break;
        case 'm': m.moves[m.movesz++] = optarg; break;
        case 'M': o_moves = true; break;
        case 'a': o_apply = true; break;
        case 'i': o_minimax = true; break;
        case '?':
        default:
            return 1;
        }
    }

    while (board_read(&m, &b1, &mm, (in)?in:stdin)) {
        
        if (b1.X != 3 || b1.Y != 3) {
            fprintf(stderr, "E Invalid board size.\n");
            goto fail_input;
        }

        winner = tictactoe_winner_and_value(&b1);

        if (!winner && b1.turn != 'x' && b1.turn != 'o') {
            fprintf(stderr, "E Invalid or missing 'turn'.\n");
            goto fail_input;
        }

        if (o_minimax) {
            minimax(&tictactoe_mx, &b1, b1.turn, 9, &m);
        }
        
        if (o_moves) {
            tictactoe_moves(&m, &b1);
        }
        
        if (o_apply) {
            for (mv=0; mv < m.movesz; mv++) {
                if (winner != '\0') {
                    fprintf(stderr, "E Move %s: Game ended\n", m.moves[mv]);
                    goto fail_apply;
                }
                memcpy(&b2, &b1, sizeof(struct board_s));
                if (!tictactoe_apply(&b2, m.moves[mv])) {
                    fprintf(stderr, "E Move %s: Invalid move\n", m.moves[mv]);
                    goto fail_apply;
                }
                tictactoe_winner_and_value(&b2);
                meta_write(&m, stdout, false);
                board_write(&b2, stdout);
            }
        }
        
        if (!o_apply || (o_apply && winner)) {
            meta_write(&m, stdout, true);
            board_write(&b1, stdout);
        }

        memset(&m, 0, sizeof(struct meta_s));
    }
    
    ret = 0;
 cleanup:
    if (in) fclose(in);
    return ret;
 fail_apply:
    goto cleanup;
 fail_input:
    goto cleanup;
}
