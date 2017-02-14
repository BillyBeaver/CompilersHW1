#ifndef INT_EXPR
#define INT_EXPR

#include "visitor.h"
#include "expr.h"

class Int_expr : public Expr {
private:
	int val;
public:
	~Int_expr() { }
	Int_expr(int i) {
		val = i;
	}
	Type* check(Context& cxt) {
		return &cxt.int_type;
	}
	int getVal() {
		return val;
	}
	void accept(Visitor& v) {
		return v.visit(this);
	}
};


#endif