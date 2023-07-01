#ifndef _BINDER_H_
#define _BINDER_H_

#include "../syntax/SyntaxNode.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

enum Type {
	INT_32,
	BOOLEAN,
	UNKNOWN
};

enum BoundNodeKind {
	LITERAL_EXP,
	UNARY_EXP,
	BINARY_EXP
};

enum BoundUnaryOperatorKind {
	IDENTITY,
	NEGATION,
	UNKNOWN // Instead of just using NULL
};

enum BoundBinaryOperatorKind {
	ADDITION,
	SUBTRACTION,
	MULTIPLICATION,
	DIVISION,
	UNKNOWN // Instead of just using NULL
};

class BoundNode {
	private:
		BoundNodeKind kind;
	public:
		virtual BoundNodeKind get_kind();
};

class BoundExpression : public virtual BoundNode {
	private:
		Type type;
	public:
		virtual Type get_type();
};

class BoundLiteralExpression final : public virtual BoundExpression {
	private:
		void* value; // We use the type to determine how to set/get
		Type type;
	public:
		BoundLiteralExpression(void* value, Type type);

		BoundNodeKind get_kind() override;
		Type get_type() override;

		void* get_value();
};

class BoundUnaryExpression final : public virtual BoundExpression {
	private:
		BoundUnaryOperatorKind operator_kind;
		BoundExpression* operand;
	public:
		BoundUnaryExpression(BoundUnaryOperatorKind operator_kind, BoundExpression* operand);

		BoundNodeKind get_kind() override;
		Type get_type() override;

		BoundUnaryOperatorKind get_operator_kind();
		BoundExpression* get_operand();
};

class BoundBinaryExpression final : public virtual BoundExpression {
	private:
		BoundExpression* left;
		BoundBinaryOperatorKind operator_kind;
		BoundExpression* right;
	public:
		BoundBinaryExpression(BoundExpression* left, BoundBinaryOperatorKind operator_kind, BoundExpression* right);

		BoundNodeKind get_kind() override;
		Type get_type() override;

		BoundExpression* get_left();
		BoundBinaryOperatorKind get_operator_kind();
		BoundExpression* get_right();
};

// This is what the type checker will do
class Binder final {
	private:
		std::vector<std::string> diagnostics;

		BoundExpression* bind_literal_expression(LiteralExpressionSyntax*);
		BoundExpression* bind_unary_expression(UnaryExpressionSyntax*);
		BoundExpression* bind_binary_expression(BinaryExpressionSyntax*);

		BoundUnaryOperatorKind bind_unary_operator_kind(SyntaxKind kind, Type operand_type);
		BoundBinaryOperatorKind bind_binary_operator_kind(SyntaxKind kind, Type left_type, Type right_type);
	public:
		// Getters
		std::vector<std::string> get_diagnostics() {
			return this -> diagnostics;
		}

		// Other methods
		BoundExpression* bind_expression(ExpressionSyntax*);
};

#endif // _BINDER_H_