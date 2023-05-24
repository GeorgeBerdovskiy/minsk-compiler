#ifndef _PARSER_H_
#define _PARSER_H_

#include "SyntaxToken.h"
#include <vector>

class Parser {
	private:
		std::vector<SyntaxToken> tokens; // Maybe not super efficient...
		int position;

		SyntaxToken* peek(int offset);
		SyntaxToken* current();
	public:
		Parser();
};

#endif // _PARSER_H_
