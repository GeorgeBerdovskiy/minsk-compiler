#include "SyntaxNode.h"

// ---- I DID THIS MYSELF - CHANGE TO MATCH HIS ---- //

SyntaxKind ExpressionSyntax::get_syntax_kind() {
	return SyntaxKind::NONE;
}




// ---- ---- ---- ---- ---- ---- ----

NumberExpressionSyntax::NumberExpressionSyntax(SyntaxToken _number_token) : number_token(_number_token) {
	// Nothing to do here
}

SyntaxToken NumberExpressionSyntax::get_number_token() {
	return this -> number_token;
}

SyntaxKind NumberExpressionSyntax::get_syntax_kind() {
	return SyntaxKind::NUMBER_EXP; 
}

// Binary expressions
BinaryExpressionSyntax::BinaryExpressionSyntax(ExpressionSyntax* _left, SyntaxToken _operator_node, ExpressionSyntax* _right)
	: operator_node(_operator_node) {
	this -> left = _left;
	this -> operator_node = _operator_node;
	this -> right = _right;
}

ExpressionSyntax* BinaryExpressionSyntax::get_left() {
	return this -> left;
}

SyntaxToken BinaryExpressionSyntax::get_operator_node() {
	return this -> operator_node;
}

ExpressionSyntax* BinaryExpressionSyntax::get_right() {
	return this -> right;
}

SyntaxKind BinaryExpressionSyntax::get_syntax_kind() {
	return SyntaxKind::BINARY_EXP;
}
