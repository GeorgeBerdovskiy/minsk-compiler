#include "Evaluator.h"

Evaluator::Evaluator(BoundExpression* _root) {
	this -> root = _root;
}

int Evaluator::evaluate() {
	return evaluate_expression(this -> root);
}

int Evaluator::evaluate_expression(BoundExpression* node) {
	if (BoundLiteralExpression* num_exp = dynamic_cast<BoundLiteralExpression*>(node)) {
		// Right now we DON'T know if value stores a pointer to a number... this is very unsafe!
		void* raw_value = num_exp -> get_value();
		return *(int*) raw_value;
	}

	if (BoundUnaryExpression* un_exp = dynamic_cast<BoundUnaryExpression*>(node)) {
		int operand = this -> evaluate_expression(un_exp -> get_operand());

		// This may be nicer as a switch statement
		switch (un_exp -> get_operator_kind()) {
			case BoundUnaryOperatorKind::IDENTITY:
				return operand;
			case BoundUnaryOperatorKind::NEGATION:
				return -operand;
			default:
				// Don't know what it is. TODO - Throw exception
				std::cerr << "ERROR - Unexpected unary expression '"
						  << syntax_kind_to_string(un_exp -> get_operator_kind())
						  << "'"
						  << std::endl;
				exit(1);
		}
	} // STOPPED HERE!!!

	if (BinaryExpressionSyntax* bin_exp = dynamic_cast<BinaryExpressionSyntax*>(node)) {
		int left = this -> evaluate_expression(bin_exp -> get_left());
		int right = this -> evaluate_expression(bin_exp -> get_right());

		if (bin_exp -> get_operator_token().get_kind() == PLUS_TOKEN) {
			return left + right;
		} else if (bin_exp -> get_operator_token().get_kind() == MINUS_TOKEN) {
			return left - right;
		} else if (bin_exp -> get_operator_token().get_kind() == STAR_TOKEN) {
			return left * right;
		} else if (bin_exp -> get_operator_token().get_kind() == SLASH_TOKEN) {
			return left / right;
		} else {
			// TODO - Throw exception instead
			std::cout << "(Should throw exception) Unexpected binary operator '" << bin_exp -> get_operator_token().get_kind() << "'" << std::endl;
			exit(1);
		}
	}

	if (ParenthesizedExpressionSyntax* paren_exp = dynamic_cast<ParenthesizedExpressionSyntax*>(node)) {
		return this -> evaluate_expression(paren_exp -> get_expression());
	}

	// TODO - Throw exception here as well
	std::cerr << "Unexpected node '" << node -> get_kind() << "'" << std::endl;
	exit(1);
}
