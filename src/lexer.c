#include "intp.h"

//////////////////////////////
//----------Lexer-------------
//////////////////////////////

// Some of these functions are available in standard
// library, but still I decided to do it myself.
static inline int _is_space(char c) {
    return (c == ' ' || c == '\t' || c == '\n');
}

static inline int _is_sym(char c) {
    return (c >= '!' && c <= '/') || 
    	   (c >= ':' && c <= '@') ||
    	   (c >= '[' && c <= '`') ||
    	   (c >= '{' && c <= '~');
}

static inline int _is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

static inline int _is_num(char c) {
    return (c >= '0' && c <= '9');
}

static inline int _is_alnum(char c) {
	return _is_alpha(c) || _is_num(c); 
}

static inline int _is_id(char c) {
    return _is_alnum(c) || c == '_';
}

// Operators. Here the order of operators is 
// important and should be corresponding to
// enum _token_type
const char *_operators[] = {
    "+", "-", "*", "/", "++", "--"
};

const char *_keywords[] = {
	"break", "case", "class", "const", 
	"continue", "define", "delete", "do", 		
	"else", "for", "if", "in",     
	"is", "import", "int", "pass",
	"real", "string", "return", "switch", 	
	"var", "void", "while"
};

#define next (void)*(buf->data++);
    		 
#define copy buf->tok[times] = *buf->data; next;  times++;
#define check(y) *buf->data == y

int _lex(intp_src_buf *buf) {
	unsigned int times = 0;
	int type = -1;

	unsigned long x =  strlen(buf->tok);
	for(unsigned short i = 0; i < x; i++) { 
	    buf->tok[i] = '\0'; 
	}
	
	while(_is_space(*buf->data)) {
        if(*buf->data == ' ') { buf->col++; }
        else if(*buf->data == '\n') { buf->line++; }
		next;	  
	}
		  
	if(_is_id(*buf->data)) {
		// Check if the first character is an alphabet or underscore
		// If it is, then the token can have numbers too i.e. identifier
		if(_is_alpha(*buf->data) || check('_')) {
			
			while(_is_alpha(*buf->data) || 
				  _is_num(*buf->data) || 
				  check('_')) {
				copy;
			}

			type = ident;
			for(unsigned int i = 0; i < sizeof(_keywords)/sizeof(char*); i++) {
				if(!strcmp(buf->tok, _keywords[i])) type = 10 + i;
			}
			
		}
		
		if(_is_num(*buf->data)) {
			
			// Check if it is a hexadecimal or binary
			if(check('0')) {
				next;
				
				switch(*buf->data) {
					case 'x': case 'X': type = hex; 		// Hexadecimal
					case 'b': case 'B': type = bin;			// Binary
					default: type = -1; 
				}
			
				// Copy twice in order to copy both '0' and 'x' or 'b'
				copy; copy;
			}
			
			// Copy all other numbers
			while(_is_num(*buf->data)) {
				copy;
			}
		}
	}
	
	else if(_is_sym(*buf->data)) {
        
        // A string
        if(check('\"') || check('\'')) {
            do {
                
                copy;
                // If found a ' or ", copy again and break
                if(check('\"') || check('\'')) { copy; break; }
           
            } while(1);
			
            type = string;
        }
        
        else { 
        
            while(_is_sym(*buf->data)) { copy; }

			for(unsigned int i = 0; i < sizeof(_operators)/sizeof(char*); i++) {
				if(!strcmp(buf->tok, _operators[i])) type = 40 + i;
			}
        }	
    }
    
	return type;
}
