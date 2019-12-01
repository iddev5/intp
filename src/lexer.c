#include "intp.h"

//////////////////////////////
//----------Lexer-------------
//////////////////////////////

#define SYMBOL_COUNT 29

// Right now only including required sumbols. May add more soon.
static char _lex_symbols[SYMBOL_COUNT] = {
    '~', '!', '@', '#',
    '%', '^', '&', '*',
    '(', ')', '-', '_',
    '+', '=', '{', '}',
    '[', ']', '|', '\\',
    ':', ';', '\"', '\'',
    '<', ',', '>', '?', '/', 
	
};

static int _is_space(char c) {
    return (c == ' ' || c == '\n');
}

static int _is_sym(char c) {
    for(int i = 0; i < SYMBOL_COUNT; i++) {
        if (c == _lex_symbols[i]) return 1;
    }
    return 0;
}

static int _is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

static int _is_num(char c) {
    return (c >= '0' && c <= '9');
}

static int _is_alnum(char c) {
	return _is_alpha(c) || _is_num(c); 
}

static int _is_id(char c) {
    return _is_alnum(c) || c == '_';
}

#define OPR_COUNT 6

char *_operators[OPR_COUNT] = {
    "+", "-", "*", "/", "++", "--"
};

#define next (void)*(info->data++);
#define send strcpy(info->word, info->tok); \
    		 for(short i = 0; i < times; i++) { \
        		info->tok[i] = '\0'; \
    		 }
#define copy info->tok[times] = *info->data; \
			 next; \
			 times++;
#define check(y) *info->data == y

int _lex(intp_info *info) {
	int times = 0;
	int type = -1;
	
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
            
            // To do: A better checking system
            if(strcmp(info->tok, "+")==0) type = op_add;
            else if(strcmp(info->tok, "-")==0) type = op_sub;
            else if(strcmp(info->tok, "++")==0) type = op_inc;
            else if(strcmp(info->tok, "--")==0) type = op_dec;
            
        }	
    }
    
    send;
	return type;
}
