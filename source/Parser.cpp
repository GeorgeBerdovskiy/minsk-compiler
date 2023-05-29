#include "Parser.h"
#include "Lexer.h"

Parser::Parser(std::string text) {
	this -> position = 0;

	std::vector<SyntaxToken> _tokens;
	
	Lexer lexer = Lexer(text);
	SyntaxToken* token;

	do {
		token = lexer.next_token();

		if (token -> get_syntax_kind() != SyntaxKind::WHITESPACE_TOKEN &&
			token -> get_syntax_kind() != SyntaxKind::BAD_TOKEN) {
			_tokens.push_back(*token);
		}
	} while(token -> get_syntax_kind() != SyntaxKind::EOF_TOKEN);

	this -> tokens = _tokens;
}

// Return pointer because we only want to see it - address is enough
SyntaxToken* Parser::peek(int offset) {
	int index = (this -> position) + offset;

	if (index >= tokens.size()) return &(this -> tokens).back();

	return &(this -> tokens)[index];
}

SyntaxToken* Parser::current() {
	return this -> peek(0);
}

SyntaxToken* Parser::next_token() {
	SyntaxToken* current = this -> current();
	this -> position += 1;
	return current;
}

SyntaxToken Parser::match(SyntaxKind kind) {
	if (this -> current() -> get_syntax_kind() == kind) return *(this -> next_token());

	// Otherwise...
	return SyntaxToken(kind, this -> current() -> get_position(), "");
}

ExpressionSyntax* Parser::parse() {
	ExpressionSyntax* left = this -> parse_primary_expression();
	ExpressionSyntax* result = NULL;

	while ( this -> current() -> get_syntax_kind() == SyntaxKind::PLUS_TOKEN ||
		this -> current() -> get_syntax_kind() == SyntaxKind::MINUS_TOKEN) {
		SyntaxToken operator_token = *(this -> next_token());
		ExpressionSyntax* right = this -> parse_primary_expression();
		
		if (left == NULL) {
			result = new BinaryExpressionSyntax(result, operator_token, right);
		} else {
			result = new BinaryExpressionSyntax(left, operator_token, right);
			left = NULL;
		}
	}

	return result;
}

ExpressionSyntax* Parser::parse_primary_expression() {
	SyntaxToken number_token = this -> match(SyntaxKind::NUMBER_TOKEN);
	return new NumberExpressionSyntax(number_token);
}
