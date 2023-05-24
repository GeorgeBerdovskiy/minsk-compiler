#ifndef _SYNTAX_NODE_H_
#define _SYNTAX_NODE_H_

#include "SyntaxToken.h"

// Serves as "base" class, not meant to be used directly
class SyntaxNode {
	public:
		virtual SyntaxKind get_syntax_kind() = 0;
};

// Also "base" class (called "abstract" in C#)
class ExpressionSyntax : public SyntaxNode { // Should this be "virtual public"?
};

class NumberSyntax final : public ExpressionSyntax {
	private:
		SyntaxToken number_token;

	public:
		NumberSyntax(SyntaxToken _number_token);

		// This may need to be a pointer?
		SyntaxToken get_number_token();
		SyntaxKind get_syntax_kind() override;
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
 * /

#endif // _SYNTAX_NODE_H_
