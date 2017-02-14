#ifndef SUB_EXPR_H
#define SUB_EXPR_H

#include "visitor.h"
#include "expr.h"

class Sub_expr : public Expr {
private:
	Expr* e1;
	Expr* e2;
public:
	~Sub_expr() { }
	Sub_expr(Expr* e1, Expr* e2, Context &cxt) {
		this->e1 = e1;
		this->e2 = e2;
		check(cxt);
	}
	Type* check(Context& cxt) {
		if(e1->check(cxt) == &cxt.int_type && e2->check(cxt) == &cxt.int_type)
			return &cxt.int_type;
		else
			assert(false && "Subtract Expression Type Error . . .");
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