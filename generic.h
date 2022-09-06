#ifndef PIPE_GAMES_GENERIC_H
#define PIPE_GAMES_GENERIC_H

#include <stdlib.h>

struct mem_s {
    size_t      bsz;
    char        b[1024];
};

struct meta_s {
    char       *moves[64];
    size_t      movesz;
};




#endif
