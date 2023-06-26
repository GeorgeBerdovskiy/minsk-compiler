#include "Parser.h"
#include "Lexer.h"

Parser::Parser(std::string text) {
	this -> position = 0;

	std::vector<SyntaxToken> _tokens;
	
	Lexer lexer = Lexer(text);
	SyntaxToken* token;

	do {
		token = lexer.lex();

		if (token -> get_kind() != SyntaxKind::WHITESPACE_TOKEN &&
			token -> get_kind() != SyntaxKind::BAD_TOKEN) {
			_tokens.push_back(*token);
		}
	} while(token -> get_kind() != SyntaxKind::EOF_TOKEN);

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

SyntaxToken Parser::match_token(SyntaxKind kind) {
	if (this -> current() -> get_kind() == kind) return *(this -> next_token());

	// Add error to diagnostics
	std::ostringstream message;
        message << "ERROR - Found token '"
		<< syntax_kind_to_string(this -> current() -> get_kind())
		<< "' but expected '"
		<< syntax_kind_to_string(kind)
		<< "'";

        this -> diagnostics.push_back(message.str());

	// Otherwise...
	return SyntaxToken(kind, this -> current() -> get_position(), "");
}

SyntaxTree Parser::parse() {
	ExpressionSyntax* expression = this -> parse_expression();

	SyntaxToken eof_token = this -> match_token(SyntaxKind::EOF_TOKEN);
	return SyntaxTree(this -> diagnostics, expression, eof_token);
}

ExpressionSyntax* Parser::parse_expression(int parent_precedence) {
	// Called with 'parent_precedence' = 0 as default
	ExpressionSyntax* left;
	int unary_operator_precedence = SyntaxFacts::get_unary_operator_precedence(this -> current() -> get_kind());

	if (unary_operator_precedence != 0 && unary_operator_precedence >= parent_precedence) {
		SyntaxToken operator_token = *(this -> next_token());
		ExpressionSyntax* operand = this -> parse_expression(unary_operator_precedence);
		left = new UnaryExpressionSyntax(operator_token, operand);
	} else {
		left = this -> parse_primary_expression();
	}

	while(true) {
		int precedence = SyntaxFacts::get_binary_operator_precedence(this -> current() -> get_kind());
		if (precedence == 0 || precedence <= parent_precedence) break;

		// Otherwise...
		SyntaxToken operator_token = *(this -> next_token());
		ExpressionSyntax* right = parse_expression(precedence);
		left = new BinaryExpressionSyntax(left, operator_token, right);
	}

	return left;
}

ExpressionSyntax* Parser::parse_primary_expression() {
	if (this -> current() -> get_kind() == SyntaxKind::OPEN_PARENTHESIS_TOKEN) {
		SyntaxToken left = *(this -> next_token());
		ExpressionSyntax* expression = this -> parse_expression();
		SyntaxToken right = this -> match_token(SyntaxKind::CLOSE_PARENTHESIS_TOKEN);

		return new ParenthesizedExpressionSyntax(left, expression, right);
	}

	SyntaxToken number_token = this -> match_token(SyntaxKind::NUMBER_TOKEN);
	return new LiteralExpressionSyntax(number_token);
}

std::vector<std::string> Parser::get_diagnostics() {
        return this -> diagnostics;
}
