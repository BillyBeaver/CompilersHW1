#ifndef NEG_EXPR_H
#define NEG_EXPR_H

#include "visitor.h"
#include "expr.h"

class Neg_expr : public Expr {
private:
	Expr* e1;
public:
	~Neg_expr() { }
	Neg_expr(Expr* e1, Context &cxt) {
		this->e1 = e1;
		check(cxt);
	}
	Type* check(Context& cxt) {
		if(e1->check(cxt) == &cxt.int_type)
			return &cxt.int_type;
		else
			assert(false && "Negation Expression Type Error . . .");
	}
	Expr* getE1() {
		return e1;
	}
	void accept(Visitor& v) {
		return v.visit(this);
	}
};

#endif