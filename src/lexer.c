#include "intp.h"

//////////////////////////////
//----------Lexer-------------
//////////////////////////////

#define OPR_COUNT 6

char *_operators[OPR_COUNT] = {
    "+", "-", "*", "/", "++", "--"
};

#define next *info->data++;
#define send strcpy(info->word, info->tok); \
    		 for(short i = 0; i < times; i++) { \
        		info->tok[i] = '\0'; \
    		 }
#define copy info->tok[times] = *info->data; \
			 next(info); \
			 times++;
#define check(y) *info->data == y

int _lex(intp_info *info) {
	int times = 0;
	int type = -1;
	
	while(intp_is_space(*info->data)) {
		next;	  
	}
		  
	if(intp_is_id(*info->data)) {
		// Check if the first character is an alphabet or underscore
		// If it is, then the token can have numbers too i.e. identifier
		if(intp_is_alpha(*info->data) || check('_')) {
			
			while(intp_is_alpha(*info->data) || 
				  intp_is_num(*info->data) || 
				  check('_')) {
				copy;
			}
			
		}
		
		if(intp_is_num(*info->data)) {
			
			
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
			while(intp_is_num(*info->data)) {
				copy;
			}
		}
	}
	
	else if(intp_is_sym(*info->data)) {
		while(intp_is_sym(*info->data)) {
			copy;
		}
		
	    if(strcmp(info->tok, "+")==0) type = op_add;
    	else if(strcmp(info->tok, "-")==0) type = op_sub;
    	else if(strcmp(info->tok, "++")==0) type = op_inc;
    	else if(strcmp(info->tok, "--")==0) type = op_dec;
	}
	
	send;
	return times;
}
