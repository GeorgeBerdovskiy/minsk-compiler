#ifndef _EVALUATOR_H_
#define _EVALUATOR_H_

#include <iostream>
#include "SyntaxNode.h"
#include "../binding/Binder.h"

class Evaluator {
	private:
		BoundExpression* root;
		int evaluate_expression(ExpressionSyntax* node);
	public:
		Evaluator(BoundExpression* _root);
		int evaluate();
};


#endif // _EVALUATOR_H_
