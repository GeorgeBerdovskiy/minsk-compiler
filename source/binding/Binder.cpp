#include "Binder.h"

// BoundLiteralExpression
BoundLiteralExpression::BoundLiteralExpression
(void* _value, Type _type) {
	this -> value = _value;
	this -> type = _type;
}

BoundNodeKind BoundLiteralExpression::get_kind() {
	return this -> BoundNodeKind::LITERAL_EXP;
}

Type BoundLiteralExpression::get_type() {
	return this -> type;
}

void* BoundLiteralExpression::get_value() {
	return this -> value;
}

// BoundUnaryExpression
BoundUnaryExpression::BoundUnaryExpression
(BoundUnaryOperatorKind _operator_kind, BoundExpression* _operand) {
	this -> operator_kind = _operator_kind;
	this -> operand = _operand;
}

BoundNodeKind BoundUnaryExpression::get_kind() {
	return this -> BoundNodeKind::UNARY_EXP;
}

Type BoundUnaryExpression::get_type() {
	return this -> operand -> get_type();
}

BoundUnaryOperatorKind BoundUnaryExpression::get_operator_kind() {
	return this -> operator_kind();
}

// BoundBinaryExpression
BoundBinaryExpression::BoundBinaryExpression
(BoundExpression* left, BoundBinaryOperatorKind _operator_kind, BoundExpression* _right) {
	this -> left = _left;
	this -> operator_kind = _operator_kind;
	this -> right = _right;
}

BoundNodeKind BoundBinaryExpression::get_kind() {
	return this -> BoundNodeKind::BINARY_EXP;
}

Type BoundBinaryExpression::get_type() {
	return this -> left -> get_type();
}

BoundExpression* BoundBinaryExpression::get_left() {
	return this -> left;
}

BoundBinaryOperatorKind BoundBinaryExpression::get_operator_kind() {
	return this -> operator_kind;
}

BoundExpression* BoundBinaryExpression::get_right() {
	return this -> right;
}

// Binder
BoundExpression* Binder::bind_literal_expression(LiteralExpressionSyntax* syntax) {
	int* value = nullptr;

	try {
		value = new int(std::stoi(syntax -> get_literal_token().get_text()));
	} catch(...) {
		value = new int(0);
	}
	
	// Note to self - we use 'static_cast' rather than 'dynamic_cast'
	return new BoundLiteralExpression(static_cast<void*>(value));
}

BoundExpression* Binder::bind_unary_expression(UnaryExpressionSyntax* syntax) {
	BoundExpression* bound_operand = this -> bind_expression(syntax -> get_operand());
	BoundUnaryOperatorKind bound_operator_kind = this -> bind_unary_operator_kind(syntax -> get_operator_token().get_kind(), bound_operand -> get_type());
	
	if (bound_operator_kind == UNKNOWN) {
		// Add error to diagnostics
		std::ostringstream message;
		
		message << "ERROR - Unary operator '"
			<< syntax -> get_operator_token().get_text()
			<< "' is not defined for type '"
			<< bound_operand -> get_type()
			<< "'";

		this -> diagnostics.push_back(message.str());

		return bound_operand; // STOPPED HERE
	}

	return new BoundUnaryExpression(bound_operator_kind, bound_operand);
}

BoundExpression* Binder::bind_binary_expression(BinaryExpressionSyntax* syntax) {
	BoundExpression* bound_left = this -> bind_expression(syntax -> get_left());
	BoundExpression* bound_right = this -> bind_expression(syntax -> get_right());
	BoundBinaryOperatorKind bound_operator_kind = this -> bind_binary_operator_kind(
		syntax -> get_operator_token().get_kind(),
		bound_left -> get_type(),
		bound_right -> get_type()
	);

	if (bound_operator_kind == UNKNOWN) {
		// Add error to diagnostics
		std::ostringstream message;
		
		message << "ERROR - Binary operator'"
			<< syntax -> get_operator_token().get_text()
			<< "' is not defined for types '"
			<< bound_left -> get_type()
			<< "' and '"
			<< bound_right -> get_type()
			<< "'";

		this -> diagnostics.push_back(message.str());

		return bound_left; // STOPPED HERE
	}


	return new BoundBinaryExpression(bound_left, bound_operator_kind, bound_right);
}

BoundUnaryOperatorKind Binder::bind_unary_operator_kind(SyntaxKind kind, Type operand_type) {
	// In the video, the below returns NULL rather than UNKNOWN - I did this myself
	if (operand_type != Type::INT_32) return BoundUnaryOperatorKind::UNKNOWN;

	switch (kind) {
		case PLUS_TOKEN:
			return BoundUnaryOperatorKind::IDENTITY;
		case MINUS_TOKEN:
			return BoundUnaryOperatorKind::NEGATION;
		default:
			// TODO - Throw exception
			std::cerr << "Unexpected unary operator "
					  << syntax_kind_to_string(kind)
					  << std::endl;
			exit(1);
	}
}

BoundBinaryOperatorKind Binder::bind_binary_operator_kind
(SyntaxKind kind, Type left_type, Type right_type) {
	if (left_type != Type::INT_32 || right_type != Type::INT_32) return UNKNOWN;

	switch (kind) {
		case PLUS_TOKEN:
			return BoundBinaryOperatorKind::ADDITION;
		case MINUS_TOKEN:
			return BoundBinaryOperatorKind::SUBTRACTION;
		case STAR_TOKEN:
			return BoundBinaryOperatorKind::MULTIPLICATION>;
		case SLASH_TOKEN:
			return BoundBinaryOperatorKind::DIVISION;
		default:
			// TODO - Throw exception
			std::cerr << "Unexpected binary operator "
					  << syntax_kind_to_string(kind)
					  << std::endl;
			exit(1);
	}
}

BoundExpression* Binder::bind_expression
(ExpressionSyntax* syntax) {
	switch (syntax -> get_kind()) {
		case LITERAL_EXP:
			return this -> bind_literal_expression(dynamic_cast<LiteralExpressionSyntax*>(syntax));
		case UNARY_EXP:
			return this -> bind_unary_expression(dynamic_cast<UnaryExpressionSyntax*>(syntax));
		case BINARY_EXP:
			return this -> bind_binary_expression(dynamic_cast<BinaryExpressionSyntax*>(syntax));
		default:
			// TODO - Throw exception
			std::cerr << "Unexpected syntax '"
					  << syntax_kind_to_string(syntax -> get_kind())
					  << "'";
			exit(1);
	}
}
