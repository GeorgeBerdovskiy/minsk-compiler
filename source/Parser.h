#ifndef _PARSER_H_
#define _PARSER_H_

#include "SyntaxNode.h"
#include <vector>

class Parser {
	private:
		std::vector<SyntaxToken> tokens; // Maybe not super efficient...
		int position;

		SyntaxToken* peek(int offset);
		SyntaxToken* current();

		SyntaxToken* next_token();
	public:
		Parser(std::string text);

		SyntaxToken match(SyntaxKind);
		ExpressionSyntax* parse();
		ExpressionSyntax* parse_primary_expression();
};

#endif // _PARSER_H_
