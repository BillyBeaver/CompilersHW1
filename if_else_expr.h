#ifndef IF_ELSE_EXPR
#define IF_ELSE_EXPR

#include "visitor.h"
#include "expr.h"

class If_else_expr : public Expr {
private:
	Expr* e1;
	Expr* e2;
	Expr* e3;
public:
	~If_else_expr() { }
	If_else_expr(Expr* e1, Expr* e2, Expr* e3, Context &cxt) {
		this->e1 = e1;
		this->e2 = e2;
		this->e3 = e3;
		check(cxt);
	}
	Type* check(Context& cxt) {
		if(e1->check(cxt) == &cxt.bool_type && e2->check(cxt) == e3->check(cxt)) {
			if(e2->check(cxt) == &cxt.bool_type)
				return &cxt.bool_type;
			else
				return &cxt.int_type;
		}
		else
			assert(false && "If Else Expression Type Error . . .");
	}
	Expr* getE1() {
		return e1;
	}
	Expr* getE2() {
		return e2;
	}
	Expr* getE3() {
		return e3;
	}
	void accept(Visitor& v) {
		return v.visit(this);
	}
};


#endif