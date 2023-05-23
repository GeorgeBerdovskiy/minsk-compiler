#include "Lexer.h"

Lexer::Lexer(std::string text) {
	this -> text = text;
}

char Lexer::get_current_char() {
	if ((this -> position) > (this -> text).size()) {
		return '\0';
	}

	return (this -> text)[this -> position];
}

void Lexer::next() {
	this -> position += 1;
}

SyntaxToken Lexer::next_token() {
	/*
	 * <numbers>
	 * + - * / ()
	 * <whitespace>
	 *
	 */

	if (isdigit(this -> get_current_char())) {
		int start = this -> position;

		while (isdigit(this -> get_current_char())) {
			this -> next();
		}

		int length = (this -> position) - start;
		std::string text = (this -> text).substr(start, length);

		// TODO - Add error handling
		int value = std::stoi(text);

		return SyntaxToken(SyntaxKind::NUMBER_TOKEN, start, text, value);
	}
}
