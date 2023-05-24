#ifndef _SYNTAX_TOKEN_H_
#define _SYNTAX_TOKEN_H_

#include <string>

enum SyntaxKind {
	NUMBER_TOKEN,
	WHITESPACE_TOKEN,
	PLUS_TOKEN,
	MINUS_TOKEN,
	STAR_TOKEN,
	SLASH_TOKEN,
	OPEN_PARENTHESIS_TOKEN,
	CLOSE_PARENTHESIS_TOKEN,
	BAD_TOKEN,
	EOF_TOKEN,

	NUMBER_EXP
};

class SyntaxToken {
	private:
		SyntaxKind kind;
		int position;
		std::string text;
	public:
		SyntaxToken(SyntaxKind kind, int position, std::string text);

		SyntaxKind get_kind();
		int get_position();
		std::string get_text();
};

#endif // _SYNTAX_TOKEN_H_
