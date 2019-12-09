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

#define next (void)*(info->data++);
    		 
#define copy info->tok[times] = *info->data; next;  times++;
#define check(y) *info->data == y

int _lex(intp_info *info) {
	unsigned int times = 0;
	int type = -1;

	unsigned long x =  strlen(info->tok);
	for(unsigned short i = 0; i < x; i++) { 
	    info->tok[i] = '\0'; 
	}
	
	while(_is_space(*info->data)) {
        if(*info->data == ' ') { info->col++; }
        else if(*info->data == '\n') { info->line++; }
		next;	  
	}
		  
	if(_is_id(*info->data)) {
		// Check if the first character is an alphabet or underscore
		// If it is, then the token can have numbers too i.e. identifier
		if(_is_alpha(*info->data) || check('_')) {
			
			while(_is_alpha(*info->data) || 
				  _is_num(*info->data) || 
				  check('_')) {
				copy;
			}

			type = ident;
			for(unsigned int i = 0; i < sizeof(_keywords)/sizeof(char*); i++) {
				if(!strcmp(info->tok, _keywords[i])) type = 10 + i;
			}
			
		}
		
		if(_is_num(*info->data)) {
			
			// Check if it is a hexadecimal or binary
			if(check('0')) {
				next;
				
				switch(*info->data) {
					case 'x': case 'X': type = hex; 		// Hexadecimal
					case 'b': case 'B': type = bin;			// Binary
					default: type = -1; 
				}
			
				// Copy twice in order to copy both '0' and 'x' or 'b'
				copy; copy;
			}
			
			// Copy all other numbers
			while(_is_num(*info->data)) {
				copy;
			}
		}
	}
	
	else if(_is_sym(*info->data)) {
        
        // A string
        if(check('\"') || check('\'')) {
            do {
                
                copy;
                // If found a ' or ", copy again and break
                if(check('\"') || check('\'')) { copy; break; }
           
            } while(1);
            
        }
        
        else { 
        
            while(_is_sym(*info->data)) { copy; }

			for(unsigned int i = 0; i < sizeof(_operators)/sizeof(char*); i++) {
				if(!strcmp(info->tok, _operators[i])) type = 40 + i;
			}
        }	
    }
    
	return type;
}
