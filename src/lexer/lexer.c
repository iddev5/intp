#include "../intp.h"

enum token_type {
    hex=-50,
    bin,
    num,

	kwd_break=-35, kwd_case, kwd_class, kwd_const,
	kwd_continue, kwd_define, kwd_delete, kwd_do, 
	kwd_else, kwd_for, kwd_if, kwd_in, 
	kwd_is, kwd_import, kwd_int, kwd_pass, 
	kwd_real, kwd_string, kwd_return, kwd_switch, 
	kwd_var, kwd_void, kwd_while,

    ident=-5,     
	string=-4,

};


/* Operators. Here the order of operators is 
 * important and should be corresponding to
 * enum token_type
 */
/*
Temporarily disabled
const char *operators[] = {
    "+", "-", "*", "/", "++", "--"
};
*/

const char *keywords[] = {
	"break", "case", "class", "const", 
	"continue", "define", "delete", "do", 		
	"else", "for", "if", "in",     
	"is", "import", "int", "pass",
	"real", "string", "return", "switch", 	
	"var", "void", "while"
};

int is_whitespace(char c) {
    return (c == ' ' || c == '\t' || c == '\n');
}

int is_sym(char c) {
    return (c >= '!' && c <= '/') || 
    	   (c >= ':' && c <= '@') ||
    	   (c >= '[' && c <= '`') ||
    	   (c >= '{' && c <= '~');
}

int is_id(char c) {
    return isalnum(c) || c == '_';
}

int is_bin(char c) {
	return (c == '0') || (c == '1');
}

/*
 *----------Lexer-------------
 */

unsigned int tok_capacity = 19;
  		 
#define copy \
	if(times >= tok_capacity) { \
		tok_capacity += 4; \
		buf->tok = realloc(buf->tok, tok_capacity); \
	} \
	buf->tok[times++] = *buf->data++; \
	buf->col++;
	
#define check(y) *buf->data == y

int intp_lex(intp_src_buf *buf) {
	unsigned int times = 0;
	buf->type = -1;

	unsigned long x =  strlen(buf->tok);
	for(unsigned short i = 0; i < x; i++) { 
	    buf->tok[i] = '\0'; 
	}
	
	while(is_whitespace(*buf->data)) {
        if(*buf->data == ' ') { buf->col++; }
        else if(*buf->data == '\n') { buf->line++; }
		(void)*buf->data++;	  
	}
		  
	if(is_id(*buf->data)) {
		/* Check if the first character is an alphabet or underscore
		 * If it is, then the token can have numbers too i.e. identifier
		 */
		if(isalpha(*buf->data) || check('_')) {
			do { copy; }
			while(isalnum(*buf->data) || check('_'));

			buf->type = ident;
			for(int i = 0; i < sizeof(keywords)/sizeof(char*); i++) {
				if(!strcmp(buf->tok, keywords[i])) {
					buf->type = kwd_break + i;
				}
			}
		}
		
		if(isdigit(*buf->data)) {
			/* Check if it is a hexadecimal or binary */
			if(check('0')) {
				(void)*buf->data++; buf->col++; 
				
				switch(*buf->data) {
					case 'x': case 'X':	buf->type = hex; break; /* Hexadecimal   */
					case 'b': case 'B': buf->type = bin; break; /* Binary        */
					default: goto _num; break;             /* Other numbers */
				}
			
				/* Copy twice in order to copy both '0' and 'x' or 'b' */
				copy; copy;

				while(!is_whitespace(*buf->data)) {
					/* If hexadecimal or binary, just copy everything 
					 * if its a valid character. 
					 */
					if((buf->type == hex && isxdigit(*buf->data)) ||
					   (buf->type == bin && is_bin(*buf->data))) { copy; }
					else {
						/* It is neither hex nor bin nor any number.
						 * It is something weird.
						 */
						buf->type = -1; 
						do {
							copy;
						} while(!is_whitespace(*buf->data));
						break;
					}
				}	
			}
			else {
			_num:
				buf->type = num;
				/* Copy all other numbers */
				while(isdigit(*buf->data)) {
					copy;
				}
			}
		}
	}
	
	else if(is_sym(*buf->data)) {
        /* A string */
        if(check('\"') || check('\'')) {
            do {
                copy;
                /* If found ' or ", copy again and break */
                if(check('\"') || check('\'')) { copy; break; }
            } while(1);
			
            buf->type = string;
        }
        
        else {
        	/* Presently it only supports singl-char operator tokens */ 
			copy; 
			buf->type = (int)*buf->tok;
		}
    }

	/* There is a function but still return anyway */
    return buf->type;
}