#ifndef BOOL_EXPR_H
#define BOOL_EXPR_H

#include "visitor.h"
#include "expr.h"

class Bool_expr : public Expr {
private:
	bool val;
public:
	~Bool_expr() { }
	Bool_expr(bool b) {
		val = b;
	}
	Type* check(Context& cxt) {
		return &cxt.bool_type;
	}
	bool getVal() {
		return val;
	}
	void accept(Visitor& v) {
		return v.visit(this);
	}
};

#endif