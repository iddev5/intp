#ifndef INTP_EXPR_H
#define INTP_EXPR_H

#include "../intp.h"

intp_data *expr(intp_src_buf *buf, intp_info *info);
intp_data *paren_expr(intp_src_buf *buf, intp_info *info);

#endif