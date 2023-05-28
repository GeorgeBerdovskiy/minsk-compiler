#ifndef _SYNTAX_NODE_H_
#define _SYNTAX_NODE_H_

#include "SyntaxToken.h"

// Serves as "base" class, not meant to be used directly
class SyntaxNode {
	private:
		std::vector<SyntaxNode> children;
	public:
		virtual std::vector<SyntaxNode> get_children();
		virtual SyntaxKind get_syntax_kind() = 0;
};

// Also "base" class (called "abstract" in C#)
class ExpressionSyntax : public virtual SyntaxNode { // Should this be "virtual public"?
	public:
		virtual SyntaxKind get_syntax_kind();
};

class NumberExpressionSyntax final : public virtual ExpressionSyntax {
	private:
		SyntaxToken number_token;

	public:
		NumberExpressionSyntax(SyntaxToken _number_token);

		// This may need to be a pointer?
		SyntaxToken get_number_token();
		virtual SyntaxKind get_syntax_kind() override;
};

class BinaryExpressionSyntax final : virtual public ExpressionSyntax {
	private:
		ExpressionSyntax* left;
		SyntaxToken operator_node;
		ExpressionSyntax* right;
	public:
		BinaryExpressionSyntax();
		BinaryExpressionSyntax(ExpressionSyntax*, SyntaxToken, ExpressionSyntax*);

		ExpressionSyntax* get_left();
		SyntaxToken get_operator_node();
		ExpressionSyntax* get_right();

		virtual SyntaxKind get_syntax_kind() override;
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
