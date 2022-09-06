#ifndef MINIMAX_H
#define MINIMAX_H

#include "generic.h"
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#ifndef BOARD_TYPE
#  define BOARD_TYPE void
#endif

struct minimax_s {
    size_t   bsz;
    char   (*get_turn) (const BOARD_TYPE *_b);
    void   (*get_moves) (struct meta_s *_m, const BOARD_TYPE *_b);
    char   (*get_winner_and_value) (BOARD_TYPE *_b);
    int    (*get_value) (const BOARD_TYPE *_b, char _pl);
    bool   (*apply_move) (BOARD_TYPE *_b, const char *_mv);
    
};

static inline int
minimax(const struct minimax_s *_mx, void *b1, char _ia, int _max_depth, struct meta_s *_opt_meta)
{
    
    char           turn      = _mx->get_turn(b1);
    bool           maximizer = _ia == turn;
    int            value     = (maximizer)?INT_MIN:INT_MAX;
    char          *value_mv  = NULL;
    struct meta_s  m         = {0};
    char           b2[_mx->bsz];
    size_t         mv;
    int            nvalue;

    _mx->get_moves(&m, b1);
    if (_mx->get_winner_and_value(b1) || _max_depth == 0 || m.movesz == 0) {
        value = _mx->get_value(b1, _ia);
    } else {
        for (mv = 0; mv<m.movesz; mv++) {
            memcpy(b2, b1, _mx->bsz);
            if (!_mx->apply_move((void*)&b2, m.moves[mv])) continue;
            nvalue = minimax(_mx, b2, _ia, _max_depth-1, NULL);
            if ( (maximizer == true  && nvalue > value) ||
                 (maximizer == false && nvalue < value) ) {
                value = nvalue;
                value_mv = m.moves[mv];
            }
        }
    }
    
    if (value_mv && _opt_meta) {
        _opt_meta->moves[_opt_meta->movesz++] = value_mv;
    }
    
    return value;
}


#endif
