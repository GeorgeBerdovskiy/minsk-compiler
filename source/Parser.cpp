#include "Parser.h"

Parser::Parser() {
	this -> position = 0;
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
