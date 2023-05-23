#ifndef _SYNTAX_TOKEN_H_
#define _SYNTAX_TOKEN_H_

enum SyntaxKind {
	NUMBER_TOKEN,
	WHITESPACE_TOKEN
};

template<typename T>
class SyntaxToken {
	private:
		SyntaxKind kind;
		int position;
		std::string text;
		T value;
	public:
		SyntaxToken(SyntaxKind kind, int position, std::string text, T& value);

		SyntaxKind get_kind();
		int get_position();
		std::string get_text();
};

#endif // _SYNTAX_TOKEN_H_
