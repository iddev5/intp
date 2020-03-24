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

/* A macro used for copying string and identifiers
 * To be used carefully 
 */
#define copy                                         \
if(times >= cap) {                                   \
    cap += 4; buf->tok = realloc(buf->tok, cap);     \
}                                                    \
if(this_ch(buf)=='\n') { buf->col=1; buf->line++; }  \
else { buf->col++; }                                 \
buf->tok[times++] = next_ch(buf);        

int intp_lex(intp_src_buf *buf) {
    buf->type = -1;
lexl:
    switch(this_ch(buf)) {
        case ' ' : buf->col++; next_ch(buf); goto lexl;
        case '\t': buf->col+=4; next_ch(buf); goto lexl;
        case '\n': buf->col=1; buf->line++; next_ch(buf); goto lexl;
        case '{' : buf->type = LBRAC;  buf->col++; next_ch(buf); break;
        case '}' : buf->type = RBRAC;  buf->col++; next_ch(buf); break;
        case '(' : buf->type = LPAREN; buf->col++; next_ch(buf); break;
        case ')' : buf->type = RPAREN; buf->col++; next_ch(buf); break;
        case '+' : buf->type = PLUS;   buf->col++; next_ch(buf); break;
        case '-' : buf->type = MINUS;  buf->col++; next_ch(buf); break; 
        case '*' : buf->type = MULTI;  buf->col++; next_ch(buf); break;
        case '/' : buf->type = DIV;  buf->col++; next_ch(buf); break;
        case '%' : buf->type = MOD;  buf->col++; next_ch(buf); break; 
        case '^' : buf->type = POW;  buf->col++; next_ch(buf); break;
        case '>' : buf->type = GRT;  buf->col++; next_ch(buf); break;
        case '<' : buf->type = LES;  buf->col++; next_ch(buf); break;
        case '=' : buf->type = EQU;  buf->col++; next_ch(buf); break;
        case ';' : buf->type = SEMI; buf->col++; next_ch(buf); break;
        case ':' : buf->type = COL;  buf->col++; next_ch(buf); break;
        case '#' : buf->type = HASH; buf->col++; next_ch(buf); break;
        case ',' : buf->type = COMMA;buf->col++; next_ch(buf); break;
        case '\"' : case '\'': {
            /* String */

            int times = 0, cap = strlen(buf->tok);
            memset(buf->tok, '\0', cap);

            next_ch(buf); buf->col++; /* Eat " or ' */

            while(this_ch(buf) != '\0') {
                copy;

                /* If an ' or " is encountered then check if the previous
                 * character is \ i.e escape sequence. If so then continue 
                 * copying else break
                 */
                if(this_ch(buf) == '\"' || this_ch(buf) == '\'') {
                    if(prev_ch(buf) == '\\') { copy; }
                    else { next_ch(buf); break; }
                }
            }

            buf->type = STRING;
            break;
        }
        case '0' : case '1': case '2': case '3': case '4':
        case '5' : case '6': case '7': case '8': case '9': {
            /* To do: Support for hex, bin and oct */
            int inn = 0;
            while(this_ch(buf) >= '0' && this_ch(buf) <= '9') {
                /* i = (i*10) + (n-'0') where 'i' is the target result 
                 * and 'n' is the current char.
                 */
                inn = ((inn)*10) + (this_ch(buf)-'0');
                next_ch(buf); buf->col++;
            }

            buf->val.inn = inn;
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
                    if(!strcmp(buf->tok, keywords[i])) buf->type = KWD_AND + i;
                }

                break;
            }
            /* Deactivated because of errors. To be fixed
            else {
                
                intp_error(buf, "Unknown character");
            } */
        }
    }

    return buf->type;
}