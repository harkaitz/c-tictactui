/* Copied from "c-trim" project. */
#ifndef STR_TRIM_H
#define STR_TRIM_H

#include <string.h>
#include <ctype.h>

static inline
char *trim(char *val) {
    if (val) {
        char *cp;
        while (isspace((unsigned char)*val)) val++;
        cp = strchr(val, '\0') - 1;
        while (cp > val && isspace((unsigned char)*cp))
            *cp-- = '\0';
        return val;
    } else {
        return NULL;
    }
}

static inline
void trim2 (char *val) {
    char *p = trim(val);
    if (p != val) {
        char *d;
        for (d = val; *p; p++,d++) {
            *d = *p;
        }
        *d = '\0';
    }
}

static inline
void trim_gaps2(char to[], const char fr[], const char _spaces[]) {
    const char    *spaces  = (_spaces)  ? _spaces  : "\r\n ";
    int            space   = 1;
    int            start   = 1;
    const char    *f       = fr;
    char          *t       = to;

    for (f = fr, t = to, space = 1; *f; f++) {
        if (strchr(spaces, *f)) {
            space = 1;
        } else {
            if (space && !start) {
                *(t++) = ' ';
            }
            *(t++) = *f;
            space = start = 0;
        }
    }
    *t = '\0';
}

static inline
void trim_gaps(char b[], char const _spaces[]) {
    trim_gaps2(b, b, _spaces);
}


#endif
/**l*
 * MIT License
 * 
 * Copyright (c) 2023 Harkaitz Agirre, harkaitz.aguirre@gmail.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **l*/
