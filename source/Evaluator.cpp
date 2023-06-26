#include "Evaluator.h"

Evaluator::Evaluator(ExpressionSyntax* _root) {
	this -> root = _root;
}

int Evaluator::evaluate() {
	return evaluate_expression(this -> root);
}

int Evaluator::evaluate_expression(ExpressionSyntax* node) {
	// BinaryExpression
	// NumberExpression
	
	if (LiteralExpressionSyntax* num_exp = dynamic_cast<LiteralExpressionSyntax*>(node)) {
		std::string text = num_exp -> get_literal_token().get_text();
		return std::stoi(text);

		// In the video he just returns n.NumberToken.Value but we can't do that here because I don't store the value
		// I could maybe do that with a void pointer or different value types for different tokens but at this point using text just seems easier
	}

	if (BinaryExpressionSyntax* bin_exp = dynamic_cast<BinaryExpressionSyntax*>(node)) {
		int left = this -> evaluate_expression(bin_exp -> get_left());
		int right = this -> evaluate_expression(bin_exp -> get_right());

		if (bin_exp -> get_operator_token().get_syntax_kind() == PLUS_TOKEN) {
			return left + right;
		} else if (bin_exp -> get_operator_token().get_syntax_kind() == MINUS_TOKEN) {
			return left - right;
		} else if (bin_exp -> get_operator_token().get_syntax_kind() == STAR_TOKEN) {
			return left * right;
		} else if (bin_exp -> get_operator_token().get_syntax_kind() == SLASH_TOKEN) {
			return left / right;
		} else {
			// TODO - Throw exception instead
			std::cout << "(Should throw exception) Unexpected binary operator '" << bin_exp -> get_operator_token().get_syntax_kind() << "'" << std::endl;
			exit(1);
		}
	}

	if (ParenthesizedExpressionSyntax* paren_exp = dynamic_cast<ParenthesizedExpressionSyntax*>(node)) {
		return this -> evaluate_expression(paren_exp -> get_expression());
	}

	// TODO - Throw exception here as well
	std::cerr << "Unexpected node '" << node -> get_syntax_kind() << "'" << std::endl;
	exit(1);
}
