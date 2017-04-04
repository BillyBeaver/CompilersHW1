#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "expr.h"

#include "and_expr.h"
#include "or_expr.h"
#include "bool_expr.h"
#include "not_expr.h"
#include "xor_expr.h"
#include "int_expr.h"
#include "gt_expr.h"
#include "gte_expr.h"
#include "lt_expr.h"
#include "lte_expr.h"
#include "if_else_expr.h"
#include "eql_expr.h"
#include "neq_expr.h"
#include "add_expr.h"
#include "sub_expr.h"
#include "mul_expr.h"
#include "div_expr.h"
#include "mod_expr.h"
#include "neg_expr.h"

class Translator {
private:
	Context cxt;
public:
	Translator() { }
	Translator(Context& c) {
		cxt = c;
	}

	Expr* onConditional(Expr* e1, Expr* e2, Expr* e3) {
		If_else_expr* e = new If_else_expr(e1, e2, e3, cxt);
		return e;
	}

	Expr* onLogicalOr(Expr* e1, Expr* e2) {
		Or_expr* e = new Or_expr(e1, e2, cxt);
		return e;
	}

	Expr* onLogicalAnd(Expr* e1, Expr * e2) {
		And_expr* e = new And_expr(e1, e2, cxt);
		return e;
	}

	Expr* onEql(Expr* e1, Expr * e2) {
		Eql_expr* e = new Eql_expr(e1, e2, cxt);
		return e;
	}

	Expr* onNeq(Expr* e1, Expr * e2) {
		Neq_expr* e = new Neq_expr(e1, e2, cxt);
		return e;
	}

	Expr* onLt(Expr* e1, Expr * e2) {
		Lt_expr* e = new Lt_expr(e1, e2, cxt);
		return e;
	}

	Expr* onLte(Expr* e1, Expr * e2) {
		Lte_expr* e = new Lte_expr(e1, e2, cxt);
		return e;
	}

	Expr* onGt(Expr* e1, Expr * e2) {
		Gt_expr* e = new Gt_expr(e1, e2, cxt);
		return e;
	}

	Expr* onGte(Expr* e1, Expr * e2) {
		Gte_expr* e = new Gte_expr(e1, e2, cxt);
		return e;
	}

	Expr* onAdd(Expr* e1, Expr * e2) {
		Add_expr* e = new Add_expr(e1, e2, cxt);
		return e;
	}

	Expr* onSub(Expr* e1, Expr * e2) {
		Sub_expr* e = new Sub_expr(e1, e2, cxt);
		return e;
	}

	Expr* onMul(Expr* e1, Expr * e2) {
		Mul_expr* e = new Mul_expr(e1, e2, cxt);
		return e;
	}

	Expr* onDiv(Expr* e1, Expr * e2) {
		Div_expr* e = new Div_expr(e1, e2, cxt);
		return e;
	}

	Expr* onMod(Expr* e1, Expr * e2) {
		Mod_expr* e = new Mod_expr(e1, e2, cxt);
		return e;
	}

	Expr* onNeg(Expr* e1) {
		Neg_expr* e = new Neg_expr(e1, cxt);
		return e;
	}

	Expr* onBool(Token* t) {
		Bool_expr* b = new Bool_expr(t->getValue());
		return b;
	}

	Expr* onInt(Token* t) {
		Int_expr* i = new Int_expr(t->getValue());
		return i;
	}
};

#endif
