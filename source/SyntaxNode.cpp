#include "SyntaxNode.h"

NumberSyntax::NumberSyntax(SyntaxToken _number_token) {
	this -> number_token = _number_token;
}

SyntaxToken NumberSyntax::get_number_token() {
	return this -> number_token;
}

SyntaxKind NumberSyntax::get_syntax_kind() {
	return SyntaxKind::NUMBER_EXP; 
}
