#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <cassert>

#include "translator.h"
#include "lexer.h"
#include "symbol_table.h"

class Parser {
private:
	std::vector<Token*> tokens;
	Translator sem;
	Symbol_table sm;

public:
	Parser() { }
	Parser(std::vector<Token*> t, Context& cxt) {
		tokens = t;
		sem = Translator(cxt);
	}

	bool eof() {
		return tokens.empty();
	}

	Token* peek() {
		if(!eof())
			return tokens.front();
		else
			return NULL;
	}

	Token_Kind lookahead() {
		Token* t = peek();
		return t->getName();
	}

	Token* consume() {
		assert(!eof());
		Token* t = tokens.front();
		tokens.erase(tokens.begin());
		return t;
	}

	Token* require(Token_Kind t) {
		assert(lookahead() == t);
		return consume();
	}

	Token* match(Token_Kind t) {
		if(lookahead() == t)
			return consume();
		else
			throw std::runtime_error("Expected Token Kind " + t);
	}

	Token* match_if(Token_Kind t) {
		if(lookahead() == t)
			return consume();
		else
			return NULL;
	}

	Expr* expression() {
		//return assignmentExpression();
		return conditionalExpression();
	}

	Expr* assignmentExpression() {
		Expr* e1 = conditionalExpression();
		while(true) {
			if(Token* t = match_if(VAR_TOKEN)) {
				Expr* e2 = expression();
				//e1 = sem.onAssignment(e1, e2);
				//sm.addSymbol();
			}
		}
	}

	Expr* conditionalExpression() {
		Expr* e1 = logicalOrExpression();
		while(true) {
			if(match_if(COND_TOKEN)) {
				Expr* e2 = expression();
				match(COL_TOKEN);
				Expr* e3 = expression();
				e1 = sem.onConditional(e1, e2, e3);
			}
			else {
				break;
			}
		}
		return e1;
	}

	Expr* logicalOrExpression() {
		Expr* e1 = logicalAndExpression();
		while(true) {
			if(match_if(OR_TOKEN)) {
				Expr* e2 = logicalAndExpression();
				e1 = sem.onLogicalOr(e1, e2);
			}
			else {
				break;
			}
		}
		return e1;
	}

	Expr* logicalAndExpression() {
		Expr* e1 = equalityExpression();
		while(true) {
			if(match_if(AND_TOKEN)) {
				Expr* e2 = equalityExpression();
				e1 = sem.onLogicalAnd(e1, e2);
			}
			else {
				break;
			}
		}
		return e1;
	}

	Expr* equalityExpression() {
		Expr* e1 = orderingExpression();
		while(true) {
			if(match_if(EQL_TOKEN)) {
				Expr* e2 = orderingExpression();
				e1 = sem.onEql(e1, e2);
			}
			if(match_if(NEQ_TOKEN)) {
				Expr* e2 = orderingExpression();
				e1 = sem.onNeq(e1, e2);
			}
			else {
				break;
			}
		}
		return e1;
	}

	Expr* orderingExpression() {
		Expr* e1 = additiveExpression();
		while(true) {
			if(match_if(LT_TOKEN)) {
				Expr* e2 = additiveExpression();
				e1 = sem.onLt(e1, e2);
			}
			if(match_if(LTE_TOKEN)) {
				Expr* e2 = additiveExpression();
				e1 = sem.onLte(e1, e2);
			}
			if(match_if(GT_TOKEN)) {
				Expr* e2 = additiveExpression();
				e1 = sem.onGt(e1, e2);
			}
			if(match_if(GTE_TOKEN)) {
				Expr* e2 = additiveExpression();
				e1 = sem.onGte(e1, e2);
			}
			else {
				break;
			}
		}
		return e1;
	}

	Expr* additiveExpression() {
		Expr* e1 = multiplicativeExpression();
		while(true) {
			if(match_if(ADD_TOKEN)) {
				Expr* e2 = multiplicativeExpression();
				e1 = sem.onAdd(e1, e2);
			}
			if(match_if(SUB_TOKEN)) {
				Expr* e2 = multiplicativeExpression();
				e1 = sem.onSub(e1, e2);
			}
			else {
				break;
			}
		}
		return e1;
	}

	Expr* multiplicativeExpression() {
		Expr* e1 = unaryExpression();
		while(true) {
			if(match_if(MUL_TOKEN)) {
				Expr* e2 = unaryExpression();
				e1 = sem.onMul(e1, e2);
			}
			if(match_if(DIV_TOKEN)) {
				Expr* e2 = unaryExpression();
				e1 = sem.onDiv(e1, e2);
			}
			if(match_if(MOD_TOKEN)) {
				Expr* e2 = unaryExpression();
				e1 = sem.onMod(e1, e2);
			}
			else {
				break;
			}
		}
		return e1;
	}

	Expr* unaryExpression() {
		if(match_if(SUB_TOKEN)) {
			Expr* e1 = unaryExpression();
			return sem.onNeg(e1);
		}
		if(match_if(NEG_TOKEN)) {
			Expr* e1 = unaryExpression();
			return sem.onNeg(e1);
		}
		else {
			return primaryExpression();
		}
	}

	Expr* primaryExpression() {
		Expr* e;
		switch(lookahead()) {
			case BOOL_TOKEN:
				return sem.onBool(consume());
				break;
			case INT_TOKEN:
				return sem.onInt(consume());
				break;
			case LPAR_TOKEN:
				consume();
				e = expression();
				match(RPAR_TOKEN);
				return e;
				break;
			default:
				throw std::runtime_error("Invalid Expression . . .");
				break;
		}
	}
};

#endif
