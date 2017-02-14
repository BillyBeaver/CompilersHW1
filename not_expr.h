#ifndef NOT_EXPR_H
#define NOT_EXPR_H

#include "visitor.h"
#include "expr.h"

class Not_expr : public Expr {
private:
	Expr* e1;
public:
	~Not_expr() { }
	Not_expr(Expr* e1, Context &cxt) {
		this->e1 = e1;
		check(cxt);
	}
	Type* check(Context& cxt) {
		if(e1->check(cxt) == &cxt.bool_type)
			return &cxt.bool_type;
		else
			assert(false && "Not Expression Type Error . . .");
	}
	Expr* getE1() {
		return e1;
	}
	void accept(Visitor& v) {
		return v.visit(this);
	}
};

#endif