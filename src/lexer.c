#include "intp.h"

const char *keywords[] = {
	"and", "break", "continue", "do", "else",   "False", "for", 
    "if",  "in",    "import",   "or", "return", "True",  "while",
    
    "puts"
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

static inline char next_ch_get(intp_src_buf *buf) {
    buf->data++; 
    return *buf->data;
}

/* A macro used for copying string and identifiers
 * To be used carefully 
 */
#define count buf->col++; buf->len++;

#define copy                                         \
if(times >= cap) {                                   \
    cap += 4; buf->tok = realloc(buf->tok, cap);     \
}                                                    \
if(this_ch(buf)=='\n') { buf->col=1; buf->line++; }  \
else { count; }                                      \
buf->tok[times++] = next_ch(buf);        

#define copy1(x)                                     \
if(times >= cap) {                                   \
    cap += 4; buf->tok = realloc(buf->tok, cap);     \
}                                                    \
if(this_ch(buf)=='\n') { buf->col=1; buf->line++; }  \
else { count; }                                      \
buf->tok[times++] = x;

/* To do: lexer init, lexer len count */

int intp_lex(intp_src_buf *buf) {
    buf->type = -1;
lexl:
    switch(this_ch(buf)) {
        case '\0': break;
        case ' ' : count; next_ch(buf); goto lexl;
        case '\t': buf->col+=4; buf->len+=4; next_ch(buf); goto lexl;
        case '\n': buf->col=1; buf->line++; buf->len++; next_ch(buf); goto lexl;
        case '{' : buf->type = LBRAC;  count; next_ch(buf); break;
        case '}' : buf->type = RBRAC;  count; next_ch(buf); break;
        case '(' : buf->type = LPAREN; count; next_ch(buf); break;
        case ')' : buf->type = RPAREN; count; next_ch(buf); break;
        case '[' : buf->type = LSQR;   count; next_ch(buf); break;
        case ']' : buf->type = RSQR;   count; next_ch(buf); break;
        case ';' : buf->type = SEMI;   count; next_ch(buf); break;
        case ':' : buf->type = COL;    count; next_ch(buf); break;
        case ',' : buf->type = COMMA;  count; next_ch(buf); break;
        case '?' : buf->type = QUES;   count; next_ch(buf); break;
        case '+' : {
            count; 
            next_ch(buf); 
            
            if(this_ch(buf) == '=') { buf->type = PLUSEQU;  count; next_ch(buf); }
            else if(this_ch(buf) == '+') { buf->type = INC; count; next_ch(buf); }
            else { buf->type = PLUS; }

            break;
        }
        case '-' : {
            count; 
            next_ch(buf);

            if(this_ch(buf) == '=') { buf->type = MINEQU;   count; next_ch(buf); }
            else if(this_ch(buf) == '-') { buf->type = DEC; count; next_ch(buf); }
            else { buf->type = MINUS; }

            break;
        } 
        case '*' : {
            count; 
            next_ch(buf); 
            
            if(this_ch(buf) == '=') { buf->type = MULEQU; count; next_ch(buf); }
            else if(this_ch(buf) == '*') {
                count; 
                next_ch(buf); 

                if(this_ch(buf) == '=') { buf->type = POWEQU; count; next_ch(buf); }    
                else { buf->type = POW; }
            }
            else { buf->type = MULTI; }

            break;
        }
        case '/' : {
            count; 
            next_ch(buf); 

            if(this_ch(buf) == '=') { buf->type = DIVEQU; count; next_ch(buf); }
            else if(this_ch(buf) == '/') {
                count; 
                next_ch(buf); 

                if(this_ch(buf) == '=') { buf->type = FLOOREQU; count; next_ch(buf); }    
                else { buf->type = FLOOR; }
            }
            else { buf->type = DIV; }

            break;
        }
        case '%' : {
            count; 
            next_ch(buf); 

            if(this_ch(buf) == '=') { buf->type = MODEQU; count; next_ch(buf); }
            else { buf->type = MOD; }

            break;
        } 
        case '^' : {
            count; 
            next_ch(buf); 
            
            if(this_ch(buf) == '=') { buf->type = XOREQU; count; next_ch(buf); }
            else { buf->type = XOR; }

            break;
        }
        case '>' : {
            count; 
            next_ch(buf); 

            if(this_ch(buf) == '=') { buf->type = GRTEQU; count; next_ch(buf); }
            else if(this_ch(buf) == '>') { 
                count; 
                next_ch(buf); 
                
                if(this_ch(buf) == '=') { buf->type = RSHEQU; count; next_ch(buf); }
                else { buf->type = RSHIFT; }
            }
            else { buf->type = GRT; }
            
            break;
        }
        case '<' : {
            count; 
            next_ch(buf); 

            if(this_ch(buf) == '=') { buf->type = LESEQU; count; next_ch(buf); }
            else if(this_ch(buf) == '<') {  
                count; 
                next_ch(buf); 

                if(this_ch(buf) == '=') { buf->type = LSHEQU, count; next_ch(buf); }
                else { buf->type = LSHIFT; }
            }
            else { buf->type = LES; }
            
            break;
        }
        case '=' : {
            count; 
            next_ch(buf); 
            
            if(this_ch(buf) == '=') { buf->type = COMP; count; next_ch(buf); }
            else { buf->type = EQU; }

            break;
        }
        case '!' : {
            count;
            next_ch(buf);

            if(this_ch(buf) == '=') { buf->type = NOTEQU; count; next_ch(buf); }
            else { buf->type = NOT; }

            break;
        } 
        case '~' : {
            count;
            next_ch(buf);

            if(this_ch(buf) == '=') { buf->type = BNOTEQU; count; next_ch(buf); }
            else { buf->type = BNOT; }

            break;
        }
        case '&' : {
            count;
            next_ch(buf);

            if(this_ch(buf) == '=') { buf->type = BANDEQU; count; next_ch(buf); }
            else { buf->type = BAND; }

            break;
        }
        case '|' : {
            count;
            next_ch(buf);

            if(this_ch(buf) == '=') { buf->type = BOREQU; count; next_ch(buf); }
            else { buf->type = BOR; }

            break;
        }
        case '#' : {
            count;
            
            /* Multi-line comments starting with #- and ending with -# */
            if(next_ch_get(buf) == '-') {
                do {
                    count;
                    next_ch(buf);
                    if((this_ch(buf) == '-' && next_ch_get(buf) == '#')) { next_ch(buf); buf->col+=2; break; }
                    if(this_ch(buf) == '\0' || this_ch(buf) == EOF) { break; }
                } while(true);
            }
            /* Single line comments starting with # and ending with \n */
            else {
                do {
                    count;
                    next_ch(buf);
                    if((this_ch(buf) == '\n') || 
                    (this_ch(buf) == '\0') || 
                    (this_ch(buf) ==  EOF)) break;
                }
                while(true);
            }

            goto lexl;
        }
        case '\"' : case '\'': {
            /* String */

            int times = 0, cap = strlen(buf->tok);
            memset(buf->tok, '\0', cap);

            next_ch(buf); count; /* Eat " or ' */

            while(this_ch(buf) != '\0') {
                /* Deal with escape-sequences. */
                if(this_ch(buf) == '\\') {
                    next_ch(buf);
                    switch(this_ch(buf)) {
                        case '\\': copy1('\\'); break;
                        case '\'': copy1('\''); break;
                        case '\"': copy1('\"'); break;
                        case 'a': copy1('\a'); break;
                        case 'b': copy1('\b'); break;
                        case 'f': copy1('\f'); break;
                        case 'n': copy1('\n'); break;
                        case 'r': copy1('\r'); break;
                        case 't': copy1('\t'); break;
                        case 'v': copy1('\v'); break;
                        case '0': break;            /* To do: Octal   */
                        case 'x': case 'X': break;  /* To do: Hex     */
                        case 'u': break;            /* To do: Unicode */
                        default: copy1(this_ch(buf)); break;
                    }
                    next_ch(buf);
                    continue;
                }

                /* End the string */
                
                /* If an ' or " is encountered then break */
                if(this_ch(buf) == '\"' || this_ch(buf) == '\'') {
                    next_ch(buf); break;
                }

                if(this_ch(buf) == '\0' || this_ch(buf) == EOF)

                copy;
            }

            buf->type = STRING;
            break;
        }
        case '0' : case '1': case '2': case '3': case '4':
        case '5' : case '6': case '7': case '8': case '9': {
            int base = 10;
            real_t num  = 0.0f;

            if(this_ch(buf) == '0') {
                next_ch(buf); count;
                
                switch(this_ch(buf)) {
                    case 'x': case 'X': base = 16; next_ch(buf); break;
                }
            }

            while(true) {
                /* i = (i*base10) + (n-'0') */
                if(this_ch(buf) >= '0' && this_ch(buf) <= '9') {
                    num = (num*base) + (this_ch(buf)-'0');
                    next_ch(buf); count;
                }
                /* i = (i*base16) + (n-['a'|'A']+0x0A) */
                else if(base == 16) {
                    if(this_ch(buf) >= 'a' && this_ch(buf) <= 'f') {
                        num = (num*base) + (this_ch(buf)-'a'+0x0A);
                        next_ch(buf); count;
                    }
                    else if(this_ch(buf) >= 'A' && this_ch(buf) <= 'F') {
                        num = (num*base) + (this_ch(buf)-'A'+0x0A);
                        next_ch(buf); count;
                    }
                    else { break; }
                }
                else { break; }
            }

            if(this_ch(buf) == '.') {
                real_t pow = 1, append = 0;

                next_ch(buf);
                while(true) {
                    /* i = (i*base10) + (n-'0') */
                    if(this_ch(buf) >= '0' && this_ch(buf) <= '9') {
                        append = (append*base) + (this_ch(buf)-'0');
                        next_ch(buf); count;
                    }
                    else { break; }
                    pow *= base;
                }
                num += append/pow;
            }

            /* To do: exponents */
            
            buf->num = num;
            buf->type = NUM;
            break;
        }
        default: {
            /* Identifier/Keywords */
            /* [a-z|A-Z|_][a-z|A-Z|_|0-9]. */

            /* Check if the first char is an alphabet or _ */
            if((this_ch(buf) >= 'a' && this_ch(buf) <= 'z') || 
               (this_ch(buf) >= 'A' && this_ch(buf) <= 'Z') ||
                this_ch(buf) == '_') {   
                int times = 0, cap = strlen(buf->tok);
                memset(buf->tok, '\0', cap);
                /* Other characters can be numbers */
                do { 
                    copy;
                } while((this_ch(buf) >= 'a' && this_ch(buf) <= 'z') || 
                        (this_ch(buf) >= 'A' && this_ch(buf) <= 'Z') ||
                        (this_ch(buf) >= '0' && this_ch(buf) <= '9') ||
                        (this_ch(buf) == '_'));

                buf->type = IDENTIFIER;

                /* Check for keyword */
                for(int i=0; i<sizeof(keywords)/sizeof(char*); i++) {
                    if(!strcmp(buf->tok, keywords[i])) { buf->type = KWD_AND + i; goto _break; }
                }

                if(!strcmp(buf->tok, "and")) { buf->type = AND; }
                else if(!strcmp(buf->tok, "or")) { buf->type = OR; }

_break:
                break;
            }
            else { intp_error(buf, "Unknown character"); } 
        }
    }

    return buf->type;
}