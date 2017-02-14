#ifndef NEQ_EXPR_H
#define NEQ_EXPR_H

#include "visitor.h"
#include "expr.h"

class Neq_expr : public Expr {
private:
	Expr* e1;
	Expr* e2;
public:
	~Neq_expr() { }
	Neq_expr(Expr* e1, Expr* e2, Context &cxt) {
		this->e1 = e1;
		this->e2 = e2;
		check(cxt);
	}
	Type* check(Context& cxt) {
		if(e1->check(cxt) == e2->check(cxt))
			return &cxt.bool_type;
		else
			assert(false && "Not Equals Expression Type Error . . .");
	}
	Expr* getE1() {
		return e1;
	}
	Expr* getE2() {
		return e2;
	}
	void accept(Visitor& v) {
		return v.visit(this);
	}
};

#endif