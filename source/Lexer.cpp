#include "Lexer.h"

Lexer::Lexer(std::string _text) {
	this -> text = _text;
	this -> position = 0;
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

std::vector<std::string> Lexer::get_diagnostics() {
	return this -> diagnostics;
}

SyntaxToken* Lexer::next_token() {
	/*
	 * <numbers>
	 * + - * / ()
	 * <whitespace>
	 *
	 */

	if (this -> position >= (this -> text).size()) {
		return new SyntaxToken(SyntaxKind::EOF_TOKEN, this -> position, "\0");
	}

	if (isdigit(this -> get_current_char())) {
		int start = this -> position;

		while (isdigit(this -> get_current_char())) {
			this -> next();
		}

		int length = (this -> position) - start;
		std::string text = (this -> text).substr(start, length);

		return new SyntaxToken(SyntaxKind::NUMBER_TOKEN, start, text);
	}

	if (isspace(this -> get_current_char())) {
		int start = this -> position;

		while (isspace(this -> get_current_char())) {
			this -> next();
		}

		int length = (this -> position) - start;
		std::string text = (this -> text).substr(start, length);

		return new SyntaxToken(SyntaxKind::WHITESPACE_TOKEN, start, text);
	}

	if (this -> get_current_char() == '+') {
		return new SyntaxToken(SyntaxKind::PLUS_TOKEN, (this -> position)++, "+");
	} else if (this -> get_current_char() == '-') {
		return new SyntaxToken(SyntaxKind::MINUS_TOKEN, (this -> position)++, "-");
	} else if (this -> get_current_char() == '*') {
		return new SyntaxToken(SyntaxKind::STAR_TOKEN, (this -> position)++, "*");
	} else if (this -> get_current_char() == '/') {
		return new SyntaxToken(SyntaxKind::SLASH_TOKEN, (this -> position)++, "/");
	} else if (this -> get_current_char() == '(') {
		return new SyntaxToken(SyntaxKind::OPEN_PARENTHESIS_TOKEN, (this -> position)++, "/");
	} else if (this -> get_current_char() == '/') {
		return new SyntaxToken(SyntaxKind::CLOSE_PARENTHESIS_TOKEN, (this -> position)++, "/");
	}

	std::ostringstream message;
	message << "ERROR - Bad character in input - '" << this -> get_current_char() << "'";

	this -> diagnostics.push_back(message.str());

	return new SyntaxToken(SyntaxKind::BAD_TOKEN, (this -> position)++, (this -> text).substr(this -> position - 1, 1));
}
