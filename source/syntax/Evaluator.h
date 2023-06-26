#ifndef _EVALUATOR_H_
#define _EVALUATOR_H_

#include <iostream>
#include "SyntaxNode.h"

class Evaluator {
	private:
		ExpressionSyntax* root;
		int evaluate_expression(ExpressionSyntax* node);
	public:
		Evaluator(ExpressionSyntax* _root);
		int evaluate();
};


#endif // _EVALUATOR_H_
