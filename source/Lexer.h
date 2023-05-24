#ifndef _LEXER_H_
#define _LEXER_H_

#include <iostream>
#include <string>
#include "SyntaxToken.h"

class Lexer {
	private:
		std::string text;
		int position;
		
		char get_current_char();
		void next();
	public:
		Lexer(std::string text);
		
		SyntaxToken next_token();
};


#endif // _LEXER_H_
