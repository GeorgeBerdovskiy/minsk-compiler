#ifndef _SYNTAX_TREE_H_
#define _SYNTAX_TREE_H_

#include <vector>
#include <string>

#include "SyntaxNode.h"
#include "Parser.h"

// Note - should be final ("sealed")
class SyntaxTree {
	private:
		ExpressionSyntax* root;
		SyntaxToken eof_token;
		std::vector<std::string> diagnostics;
	public:
		SyntaxTree(std::vector<std::string>, ExpressionSyntax*, SyntaxToken);

		ExpressionSyntax* get_root();
		SyntaxToken get_eof_token();
		std::vector<std::string> get_diagnostics();

		static SyntaxTree parse(std::string);
};

#endif // _SYNTAX_TREE_H_
