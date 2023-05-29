#include "SyntaxNode.h"

SyntaxToken::SyntaxToken(SyntaxKind _kind, int _position, std::string _text) {
	this -> kind = _kind;
	this -> position = _position;
	this -> text = _text;
}

SyntaxKind SyntaxToken::get_syntax_kind() {
	return this -> kind;
}

int SyntaxToken::get_position() {
	return this -> position;
}

std::string SyntaxToken::get_text() {
	return this -> text;
}

std::vector<SyntaxNode*> SyntaxToken::get_children() {
	std::vector<SyntaxNode*> empty;
	return empty;
}