#ifndef GT_EXPR_H
#define GT_EXPR_H

#include "visitor.h"
#include "expr.h"

class Gt_expr : public Expr {
private:
	Expr* e1;
	Expr* e2;
public:
	~Gt_expr() { }
	Gt_expr(Expr* e1, Expr* e2, Context &cxt) {
		this->e1 = e1;
		this->e2 = e2;
		check(cxt);
	}
	Type* check(Context& cxt) {
		if(e1->check(cxt) == &cxt.int_type && e2->check(cxt) == &cxt.int_type)
			return &cxt.bool_type;
		else
			assert(false && "Greater Than Expression Type Error . . .");
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