#ifndef PRINT_H
#define PRINT_H

#include <iostream>
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

bool parenCheck(Expr* e) {
	class V : public Visitor {
	public:
		bool r;
		void visit(Bool_expr* e) {
			r = false;
		}
		void visit(Int_expr* e) {
			r = false;
		}
		void visit(And_expr* e) {
			r = true;
		}
		void visit(Or_expr* e) {
			r = true;
		}
		void visit(Not_expr* e) {
			r = true;
		}
		void visit(Xor_expr* e) {
			r = true;
		}
		void visit(Eql_expr* e) {
			r = true;
		}
		void visit(Neq_expr* e) {
			r = true;
		}
		void visit(Lt_expr* e) {
			r = true;
		}
		void visit(Lte_expr* e) {
			r = true;
		}
		void visit(Gt_expr* e) {
			r = true;
		}
		void visit(Gte_expr* e) {
			r = true;
		}
		void visit(If_else_expr* e) {
			r = true;
		}
		void visit(Add_expr* e) {
			r = true;
		}
		void visit(Sub_expr* e) {
			r = true;
		}
		void visit(Mul_expr* e) {
			r = true;
		}
		void visit(Div_expr* e) {
			r = true;
		}
		void visit(Mod_expr* e) {
			r = true;
		}
		void visit(Neg_expr* e) {
			r = true;
		}
	};

	V vis;
	e->accept(vis);
	return vis.r;
}

void print(Expr* e) {
	class V : public Visitor {
		void printEnclosed(Expr* e) {
			if(parenCheck(e)) {
				std::cout << '(';
				print(e);
				std::cout << ')';
			}
			else {
				print(e);
			}
		}

		void visit(Bool_expr* e) {
			if(e->getVal()) {
				std::cout << "true";
			}
			else {
				std::cout << "false";
			}
		}
		void visit(Int_expr* e) {
			std::cout << e->getVal();
		}
		void visit(And_expr* e) {
			printEnclosed(e->getE1());
			std::cout << '&';
			printEnclosed(e->getE2());
		}
		void visit(Or_expr* e) {
			printEnclosed(e->getE1());
			std::cout << '|';
			printEnclosed(e->getE2());
		}
		void visit(Not_expr* e) {
			std::cout << '!';
			printEnclosed(e->getE1());
		}
		void visit(Xor_expr* e) {
			printEnclosed(e->getE1());
			std::cout << '^';
			printEnclosed(e->getE2());
		}
		void visit(Eql_expr* e) {
			printEnclosed(e->getE1());
			std::cout << " == ";
			printEnclosed(e->getE2());
		}
		void visit(Neq_expr* e) {
			printEnclosed(e->getE1());
			std::cout << " != ";
			printEnclosed(e->getE2());
		}
		void visit(If_else_expr* e) {
			std::cout << "if ";
			printEnclosed(e->getE1());
			std::cout << " then ";
			printEnclosed(e->getE2());
			std::cout << " else ";
			printEnclosed(e->getE3());
		}
		void visit(Lt_expr* e) {
			printEnclosed(e->getE1());
			std::cout << " < ";
			printEnclosed(e->getE2());
		}
		void visit(Lte_expr* e) {
			printEnclosed(e->getE1());
			std::cout << " <= ";
			printEnclosed(e->getE2());
		}
		void visit(Gt_expr* e) {
			printEnclosed(e->getE1());
			std::cout << " > ";
			printEnclosed(e->getE2());
		}
		void visit(Gte_expr* e) {
			printEnclosed(e->getE1());
			std::cout << " >= ";
			printEnclosed(e->getE2());
		}
		void visit(Add_expr* e) {
			printEnclosed(e->getE1());
			std::cout << " + ";
			printEnclosed(e->getE2());
		}
		void visit(Sub_expr* e) {
			printEnclosed(e->getE1());
			std::cout << " - ";
			printEnclosed(e->getE2());
		}
		void visit(Mul_expr* e) {
			printEnclosed(e->getE1());
			std::cout << " * ";
			printEnclosed(e->getE2());
		}
		void visit(Div_expr* e) {
			printEnclosed(e->getE1());
			std::cout << " / ";
			printEnclosed(e->getE2());
		}
		void visit(Mod_expr* e) {
			printEnclosed(e->getE1());
			std::cout << " % ";
			printEnclosed(e->getE2());
		}
		void visit(Neg_expr* e) {
			std::cout << "-";
			printEnclosed(e->getE1());
		}
	};
	V vis;
	e->accept(vis);
}

#endif