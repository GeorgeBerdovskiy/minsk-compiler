#ifndef _PARSER_H_
#define _PARSER_H_

#include "SyntaxNode.h"
#include "SyntaxTree.h"

#include <vector>
#include <sstream>

class SyntaxTree;

class Parser {
	private:
		std::vector<SyntaxToken> tokens; // Maybe not super efficient...
		int position;

		SyntaxToken* peek(int offset);
		SyntaxToken* current();

		ExpressionSyntax* parse_expression();

		SyntaxToken* next_token();
		std::vector<std::string> diagnostics;
	public:
		Parser(std::string text);

		SyntaxToken match_token(SyntaxKind);
		SyntaxTree parse();

		ExpressionSyntax* parse_term();
		ExpressionSyntax* parse_factor();
		ExpressionSyntax* parse_primary_expression();

		std::vector<std::string> get_diagnostics();
};

#endif // _PARSER_H_
