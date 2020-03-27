#ifndef INTP_EXPR_H
#define INTP_EXPR_H

#include "../intp.h"

intp_data *expr(intp_src_buf *buf, intp_info *info);
intp_data *paren_expr(intp_src_buf *buf, intp_info *info);

/*
 * Private Functions
 * It is not recomended to use these functions
 * for general purpose.
 */

static inline int64_t FLOORf(real_t x) {
    return (int64_t)(x < 0 ? (x - 0.5) : (x + 0.5));
}

static inline real_t POWf(real_t x, real_t y) {
    real_t res = 1;
    for(int i = 0; i < (num_t)y; i++) {
        res *= x;
    }
    return res;
}

#endif