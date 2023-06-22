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
	
	// Add diagnostics from lexer to parser
	for (auto message : lexer.get_diagnostics()) {
		this -> diagnostics.push_back(message);
	}
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

	// Add error to diagnostics
	std::ostringstream message;
        message << "ERROR - Found token '"
		<< syntax_kind_to_string(this -> current() -> get_syntax_kind())
		<< "' but expected '"
		<< syntax_kind_to_string(kind)
		<< "'";

        this -> diagnostics.push_back(message.str());

	// Otherwise...
	return SyntaxToken(kind, this -> current() -> get_position(), "");
}

SyntaxTree Parser::parse() {
	ExpressionSyntax* expression = this -> parse_term();

	SyntaxToken eof_token = this -> match(SyntaxKind::EOF_TOKEN);
	return SyntaxTree(this -> diagnostics, expression, eof_token);
}

ExpressionSyntax* Parser::parse_expression() {
	return this -> parse_term();
}

ExpressionSyntax* Parser::parse_term() {
	ExpressionSyntax* left = this -> parse_factor();
	ExpressionSyntax* result = left;

	while ( this -> current() -> get_syntax_kind() == SyntaxKind::PLUS_TOKEN ||
		this -> current() -> get_syntax_kind() == SyntaxKind::MINUS_TOKEN) {
		SyntaxToken operator_token = *(this -> next_token());
		ExpressionSyntax* right = this -> parse_factor();
		
		if (left == NULL) {
			result = new BinaryExpressionSyntax(result, operator_token, right);
		} else {
			result = new BinaryExpressionSyntax(left, operator_token, right);
			left = NULL;
		}
	}

	return result;
}

ExpressionSyntax* Parser::parse_factor() {
	ExpressionSyntax* left = this -> parse_primary_expression();
	ExpressionSyntax* result = left;

	while ( this -> current() -> get_syntax_kind() == SyntaxKind::STAR_TOKEN ||
		this -> current() -> get_syntax_kind() == SyntaxKind::SLASH_TOKEN) {
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
	if (this -> current() -> get_syntax_kind() == SyntaxKind::OPEN_PARENTHESIS_TOKEN) {
		SyntaxToken left = *(this -> next_token());
		ExpressionSyntax* expression = this -> parse_expression();
		SyntaxToken right = this -> match(SyntaxKind::CLOSE_PARENTHESIS_TOKEN);

		return new ParenthesizedExpressionSyntax(left, expression, right);
	}

	SyntaxToken number_token = this -> match(SyntaxKind::NUMBER_TOKEN);
	return new NumberExpressionSyntax(number_token);
}

std::vector<std::string> Parser::get_diagnostics() {
        return this -> diagnostics;
}
