#ifndef _SYNTAX_FACTS_
#define _SYNTAX_FACTS_

#include "SyntaxNode.h"

class SyntaxFacts final {
	public:
		static int get_unary_operator_precedence(SyntaxKind kind) {
			switch (kind) {
				case PLUS_TOKEN:
				case MINUS_TOKEN:
					return 3;

				default:
					return 0;
			}
		}

		static int get_binary_operator_precedence(SyntaxKind kind) {
			switch (kind) {
				case STAR_TOKEN:
				case SLASH_TOKEN:
					return 2;

				case PLUS_TOKEN:
				case MINUS_TOKEN:
					return 1;

				default:
					return 0;
			}
		}
};

#endif // _SYNTAX_FACTS_