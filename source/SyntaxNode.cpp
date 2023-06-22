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
	case NUMBER_EXP:
		return "NUMBER_EXP";
	case BINARY_EXP:
		return "BINARY_EXP";
	case PARENTHESIZED_EXP:
		return "PARENTHESIZED_EXP";
	default:
		return "NONE";
	}
}


// NumberExpressionSyntax
NumberExpressionSyntax::NumberExpressionSyntax(SyntaxToken _number_token) : number_token(_number_token) {
	// Nothing to do here
}

SyntaxToken NumberExpressionSyntax::get_number_token() {
	return this -> number_token;
}

SyntaxKind NumberExpressionSyntax::get_syntax_kind() {
	return SyntaxKind::NUMBER_EXP; 
}

std::vector<SyntaxNode*> NumberExpressionSyntax::get_children() {
	std::vector<SyntaxNode*> result;
	result.push_back(&(this -> number_token));
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

SyntaxKind BinaryExpressionSyntax::get_syntax_kind() {
	return SyntaxKind::BINARY_EXP;
}

std::vector<SyntaxNode*> BinaryExpressionSyntax::get_children() {
	std::vector<SyntaxNode*> result;

	result.push_back(this -> left);
	result.push_back(&(this -> operator_token));
	result.push_back(this -> right);

	return result;
}

ParenthesizedExpressionSyntax::ParenthesizedExpressionSyntax(SyntaxToken _open_parenthesis_token, ExpressionSyntax* _expression, SyntaxToken _close_parenthesis_token) : open_parenthesis_token(_open_parenthesis_token), close_parenthesis_token(_close_parenthesis_token) {
	this -> expression = _expression;
}

ExpressionSyntax* ParenthesizedExpressionSyntax::get_expression() {
	return this -> expression;
}

SyntaxKind ParenthesizedExpressionSyntax::get_syntax_kind() {
	return SyntaxKind::PARENTHESIZED_EXP;
}

std::vector<SyntaxNode*> ParenthesizedExpressionSyntax::get_children() {
	std::vector<SyntaxNode*> result;

	result.push_back(&(this -> open_parenthesis_token));
	result.push_back(this -> expression);
	result.push_back(&(this -> close_parenthesis_token));

	return result;
}
