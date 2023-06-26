#ifndef _SYNTAX_NODE_H_
#define _SYNTAX_NODE_H_

#include <string>
#include <vector>

enum SyntaxKind {
	NONE,

	// Tokens
	BAD_TOKEN,
	EOF_TOKEN,
	WHITESPACE_TOKEN,
	NUMBER_TOKEN,
	PLUS_TOKEN,
	MINUS_TOKEN,
	STAR_TOKEN,
	SLASH_TOKEN,
	OPEN_PARENTHESIS_TOKEN,
	CLOSE_PARENTHESIS_TOKEN,

	// Expressions
	LITERAL_EXP,
	UNARY_EXP,
	BINARY_EXP,
	PARENTHESIZED_EXP
};

std::string syntax_kind_to_string(SyntaxKind kind);

// Serves as "base" class, not meant to be used directly
class SyntaxNode {
	private:
		SyntaxKind kind;
	public:
		virtual std::vector<SyntaxNode*> get_children() = 0;
		virtual SyntaxKind get_kind() = 0;
};

class SyntaxToken : public virtual SyntaxNode {
	private:
		SyntaxKind kind;
		int position;
		std::string text;
	public:
		// Constructor
		SyntaxToken(SyntaxKind kind, int position, std::string text);

		// Getters
		int get_position();
		std::string get_text();

		// Virtual class member overrides
		SyntaxKind get_kind() override;
		std::vector<SyntaxNode*> get_children() override;
};

class ExpressionSyntax : public virtual SyntaxNode {
	// Nothing needed here
};

class LiteralExpressionSyntax final : public virtual ExpressionSyntax {
	private:
		SyntaxToken literal_token;

	public:
		// Constructor
		LiteralExpressionSyntax(SyntaxToken _literal_token);

		// Getters
		SyntaxToken get_literal_token();

		// Virtual class member overrides
		SyntaxKind get_kind() override;
		std::vector<SyntaxNode*> get_children() override;
};

class BinaryExpressionSyntax final : virtual public ExpressionSyntax {
	private:
		ExpressionSyntax* left;
		SyntaxToken operator_token;
		ExpressionSyntax* right;
	public:
		// Constructors
		BinaryExpressionSyntax(ExpressionSyntax*, SyntaxToken, ExpressionSyntax*);

		// Getters
		ExpressionSyntax* get_left();
		SyntaxToken get_operator_token();
		ExpressionSyntax* get_right();

		// Virtual class member overrides
		SyntaxKind get_kind() override;
		std::vector<SyntaxNode*> get_children() override;
};

class UnaryExpressionSyntax final : virtual public ExpressionSyntax {
	private:
		SyntaxToken operator_token;
		ExpressionSyntax* operand;
	public:
		// Constructors
		UnaryExpressionSyntax(SyntaxToken, ExpressionSyntax*);

		// Getters
		SyntaxToken get_operator_token();
		ExpressionSyntax* get_operand();

		// Virtual class member overrides
		SyntaxKind get_kind() override;
		std::vector<SyntaxNode*> get_children() override;
};

class ParenthesizedExpressionSyntax final : virtual public ExpressionSyntax {
	private:
		SyntaxToken open_parenthesis_token;
		ExpressionSyntax* expression;
		SyntaxToken close_parenthesis_token;
	public:
		ParenthesizedExpressionSyntax(SyntaxToken, ExpressionSyntax*, SyntaxToken);
		
		ExpressionSyntax* get_expression();

		SyntaxKind get_kind() override;
		std::vector<SyntaxNode*> get_children() override;
};

/*
 * 1 + 2 * 3
 *
 *      +
 *     / \
 *    1   *
 *       / \
 *      2   3
 *
 *
 * 1 = Number node
 * + = binary operator node
 *
 */

#endif // _SYNTAX_NODE_H_
