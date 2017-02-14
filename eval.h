#ifndef EVAL_H
#define EVAL_H

#include <iostream>
#include <climits>
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

int eval(Expr* e) {
	class V : public Visitor {
	public:
		int r;
		void visit(Bool_expr* e) {
			r = e->getVal();
		}
		void visit(And_expr* e) {
			r = eval(e->getE1()) & eval(e->getE2());
		}
		void visit(Or_expr* e) {
			r = eval(e->getE1()) | eval(e->getE2());
		}
		void visit(Not_expr* e) {
			r = !eval(e->getE1());
		}
		void visit(Xor_expr* e) {
			r = (eval(e->getE1()) != eval(e->getE2()));
		}
		void visit(If_else_expr* e) {
			if(eval(e->getE1()))
				r = eval(e->getE2());
			else
				r = eval(e->getE3());
		}
		void visit(Eql_expr* e) {
			r = (eval(e->getE1()) == eval(e->getE2()));
		}
		void visit(Neq_expr* e) {
			r = (eval(e->getE1()) != eval(e->getE2()));
		}
		void visit(Int_expr* e) {
			r = e->getVal();
		}
		void visit(Lt_expr* e) {
			r = (eval(e->getE1()) < eval(e->getE2()));
		}
		void visit(Lte_expr* e) {
			r = (eval(e->getE1()) <= eval(e->getE2()));
		}
		void visit(Gt_expr* e) {
			r = (eval(e->getE1()) > eval(e->getE2()));
		}
		void visit(Gte_expr* e) {
			r = (eval(e->getE1()) >= eval(e->getE2()));
		}
		void visit(Add_expr* e) {
			if(eval(e->getE1()) > 0 && eval(e->getE2()) > INT_MAX - eval(e->getE1()))
				assert(false && "Addition Overflow Error");
			else
				r = (eval(e->getE1()) + eval(e->getE2()));
		}
		void visit(Sub_expr* e) {
			if(eval(e->getE1()) < 0 && eval(e->getE2()) > INT_MIN + eval(e->getE1()))
				assert(false && "Subtraction Overflow Error");
			else
				r = (eval(e->getE1()) - eval(e->getE2()));
		}
		void visit(Mul_expr* e) {
			if(eval(e->getE1()) != 0 && (eval(e->getE1()) * eval(e->getE2())) / eval(e->getE1()) != eval(e->getE2()))
				assert(false && "Multiplication Overflow Error");
			else
				r = (eval(e->getE1()) * eval(e->getE2()));
		}
		void visit(Div_expr* e) {
			if(eval(e->getE2()) == 0)
				assert(false && "Division By Zero Error");
			else if(eval(e->getE2()) == -1 && eval(e->getE1()) - INT_MIN)
				assert(false && "Division Overflow Error");
			else
				r = (eval(e->getE1()) / eval(e->getE2()));
		}
		void visit(Mod_expr* e) {
			if(eval(e->getE2()) == 0)
				assert(false && "Division By Zero Error");
			else
				r = (eval(e->getE1()) % eval(e->getE2()));
		}
		void visit(Neg_expr* e) {
			if(eval(e->getE1()) == INT_MIN)
				assert(false && "Negation Overflow Error");
			else
				r = (0 - eval(e->getE1()));
		}
	};
	V vis;
	e->accept(vis);
	return vis.r;
}

#endif