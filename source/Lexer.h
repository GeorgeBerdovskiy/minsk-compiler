#ifndef _LEXER_H_
#define _LEXER_H_

#include <iostream>
#include <string>
#include <sstream>

#include "SyntaxNode.h"

class Lexer {
	private:
		std::string text;
		int position;
		
		char get_current_char();
		void next();

		std::vector<std::string> diagnostics;
	public:
		Lexer(std::string text);
		
		SyntaxToken* next_token();
		std::vector<std::string> get_diagnostics();
};


#endif // _LEXER_H_
