#include "SyntaxNode.h"

std::string syntax_kind_to_string(SyntaxKind kind) {
	switch(kind) {
	case NUMBER_TOKEN:
		return "NUMBER_TOKEN";
	case WHITESPACE_TOKEN:
		return "WHITESPACE_TOKEN";
	case PLUS_TOKEN:
		return "PLUS_TOKEN";
	case MINUS_TOKEN:
		return "MINUS_TOKEN";
	case STAR_TOKEN:
		return "STAR_TOKEN";
	case SLASH_TOKEN:
		return "SLASH_TOKEN";
	case OPEN_PARENTHESIS_TOKEN:
		return "OPEN_PARENTHESIS_TOKEN";
	case CLOSE_PARENTHESIS_TOKEN:
		return "CLOSE_PARENTHESIS_TOKEN";
	case BAD_TOKEN:
		return "BAD_TOKEN";
	case EOF_TOKEN:
		return "EOF_TOKEN";
	case LITERAL_EXP:
		return "LITERAL_EXP";
	case UNARY_EXP:
		return "UNARY_EXP";
	case BINARY_EXP:
		return "BINARY_EXP";
	case PARENTHESIZED_EXP:
		return "PARENTHESIZED_EXP";
	default:
		return "NONE";
	}
}


// LiteralExpressionSyntax
LiteralExpressionSyntax::LiteralExpressionSyntax(SyntaxToken _literal_token) : literal_token(_literal_token) {
	// Nothing to do here
}

SyntaxToken LiteralExpressionSyntax::get_literal_token() {
	return this -> literal_token;
}

SyntaxKind LiteralExpressionSyntax::get_kind() {
	return SyntaxKind::LITERAL_EXP; 
}

std::vector<SyntaxNode*> LiteralExpressionSyntax::get_children() {
	std::vector<SyntaxNode*> result;
	result.push_back(&(this -> literal_token));
	return result;
}

// BinaryExpressionSyntax
BinaryExpressionSyntax::BinaryExpressionSyntax(ExpressionSyntax* _left, SyntaxToken _operator_token, ExpressionSyntax* _right)
	: operator_token(_operator_token) {
	this -> left = _left;
	this -> right = _right;
}

ExpressionSyntax* BinaryExpressionSyntax::get_left() {
	return this -> left;
}

SyntaxToken BinaryExpressionSyntax::get_operator_token() {
	return this -> operator_token;
}

ExpressionSyntax* BinaryExpressionSyntax::get_right() {
	return this -> right;
}

SyntaxKind BinaryExpressionSyntax::get_kind() {
	return SyntaxKind::BINARY_EXP;
}

std::vector<SyntaxNode*> BinaryExpressionSyntax::get_children() {
	std::vector<SyntaxNode*> result;

	result.push_back(this -> left);
	result.push_back(&(this -> operator_token));
	result.push_back(this -> right);

	return result;
}

// UnaryExpressionSyntax
UnaryExpressionSyntax::UnaryExpressionSyntax(SyntaxToken _operator_token, ExpressionSyntax* _operand)
	: operator_token(_operator_token) {
	this -> operand = _operand;
}

SyntaxToken UnaryExpressionSyntax::get_operator_token() {
	return this -> operator_token;
}

ExpressionSyntax* UnaryExpressionSyntax::get_operand() {
	return this -> operand;
}

SyntaxKind UnaryExpressionSyntax::get_kind() {
	return UNARY_EXP;
}

std::vector<SyntaxNode*> UnaryExpressionSyntax::get_children() {
	std::vector<SyntaxNode*> result;

	result.push_back(&(this -> operator_token));
	result.push_back(this -> operand);

	return result;
}

// ParenthesizedExpressionSyntax
ParenthesizedExpressionSyntax::ParenthesizedExpressionSyntax(SyntaxToken _open_parenthesis_token, ExpressionSyntax* _expression, SyntaxToken _close_parenthesis_token) : open_parenthesis_token(_open_parenthesis_token), close_parenthesis_token(_close_parenthesis_token) {
	this -> expression = _expression;
}

ExpressionSyntax* ParenthesizedExpressionSyntax::get_expression() {
	return this -> expression;
}

SyntaxKind ParenthesizedExpressionSyntax::get_kind() {
	return SyntaxKind::PARENTHESIZED_EXP;
}

std::vector<SyntaxNode*> ParenthesizedExpressionSyntax::get_children() {
	std::vector<SyntaxNode*> result;

	result.push_back(&(this -> open_parenthesis_token));
	result.push_back(this -> expression);
	result.push_back(&(this -> close_parenthesis_token));

	return result;
}
