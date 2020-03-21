#include "intp.h"

const char *keywords[] = {
	"and", "break", "continue", "do", "else",   "False", "for", 
    "if",  "in",    "import",   "or", "return", "True",  "while"
};

static inline char this_ch(intp_src_buf *buf) {
    return *buf->data;
}

static inline char prev_ch(intp_src_buf *buf) {
    return *(buf->data-1);
}

static inline char next_ch(intp_src_buf *buf) {
    return *buf->data++;
}

#define copy if(times >= cap) { cap += 4; buf->tok = realloc(buf->tok, cap); } \
buf->tok[times++] = next_ch(buf);

int intp_lex(intp_src_buf *buf) {
    buf->type = -1;
lexl:
    switch(this_ch(buf)) {
        case ' ' : case '\t': next_ch(buf); goto lexl;
        case '\n': buf->type = EOL; next_ch(buf); break;
        case '{' : buf->type = LBRAC;  next_ch(buf); break;
        case '}' : buf->type = RBRAC;  next_ch(buf); break;
        case '(' : buf->type = LPAREN; next_ch(buf); break;
        case ')' : buf->type = RPAREN; next_ch(buf); break;
        case '+' : buf->type = PLUS;  next_ch(buf); break;
        case '-' : buf->type = MINUS; next_ch(buf); break; 
        case '*' : buf->type = MULTI; next_ch(buf); break;
        case '/' : buf->type = DIV; next_ch(buf); break;
        case '%' : buf->type = MOD; next_ch(buf); break; 
        case '^' : buf->type = POW; next_ch(buf); break;
        case '>' : buf->type = GRT; next_ch(buf); break;
        case '<' : buf->type = LES; next_ch(buf); break;
        case '=' : buf->type = EQU; next_ch(buf); break;
        case ';' : buf->type = SEMI; next_ch(buf); break;
        case ':' : buf->type = COL;  next_ch(buf); break;
        case '#' : buf->type = HASH; next_ch(buf); break;
        case '\"' : case '\'': {
            int times = 0, cap = strlen(buf->tok);
            memset(buf->tok, '\0', cap);

            next_ch(buf); /* Eat " or ' */

            while(this_ch(buf) != '\0') {
                copy;

                if(this_ch(buf) == '\"' || this_ch(buf) == '\'') {
                    if(prev_ch(buf) == '\\') { copy; }
                    else { break; }
                }
            }

            buf->type = STRING;
            break;
        }
        case '0' : case '1': case '2': case '3': case '4':
        case '5' : case '6': case '7': case '8': case '9': {
            int inn = 0;
            while(this_ch(buf) >= '0' && this_ch(buf) <= '9') {
                inn = ((inn)*10) + (this_ch(buf)-'0');
                next_ch(buf);
            }

            buf->val.inn = inn;
            buf->type = NUM;

            break;
        }
        default: {
            if((this_ch(buf) >= 'a' && this_ch(buf) <= 'z') || 
               (this_ch(buf) >= 'A' && this_ch(buf) <= 'Z')) {   
                int times = 0, cap = strlen(buf->tok);
                memset(buf->tok, '\0', cap);
                do { 
                    copy;
                } while((this_ch(buf) >= 'a' && this_ch(buf) <= 'z') || 
                        (this_ch(buf) >= 'A' && this_ch(buf) <= 'Z') ||
                        (this_ch(buf) >= '0' && this_ch(buf) <= '9') ||
                        (this_ch(buf) == '_'));

                buf->type = IDENTIFIER;

                for(int i=0; i<sizeof(keywords)/sizeof(char*); i++) {
                    if(!strcmp(buf->tok, keywords[i])) buf->type = KWD_AND + i;
                }

                break;
            }
        }
    }

    return buf->type;
}