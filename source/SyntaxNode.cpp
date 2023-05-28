#include "SyntaxNode.h"

// ---- I DID THIS MYSELF - CHANGE TO MATCH HIS ---- //

SyntaxKind ExpressionSyntax::get_syntax_kind() {
	return SyntaxKind::NONE;
}




// ---- ---- ---- ---- ---- ---- ----

NumberSyntax::NumberExpressionSyntax(SyntaxToken _number_token) {
	this -> number_token = _number_token;
}

SyntaxToken NumberExpressionSyntax::get_number_token() {
	return this -> number_token;
}

SyntaxKind NumberExpressionSyntax::get_syntax_kind() {
	return SyntaxKind::NUMBER_EXP; 
}

// Binary expressions
BinaryExpressionSyntax::BinaryExpressionSyntax(ExpressionSyntax* _left, SyntaxToken _operator_node, ExpressionSyntax* _right) {
	this -> left = _left;
	this -> operator_node = _operator_node;
	this -> right = _right;
}

ExpressionSyntax* get_left() {
	return this -> left;
}

SyntaxNode get_operator_node() {
	return this -> operator_node;
}

ExpressionSyntax* get_right() {
	return this -> right;
}

SyntaxKind BinaryExpressionSyntax::get_syntax_kind() {
	return SyntaxKind::BINARY_EXP;
}
