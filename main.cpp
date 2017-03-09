#include <iostream>
#include <vector>
#include <math.h>

#include "eval.h"
#include "print.h"
#include "type.h"
#include "lexer.h"

int main() {
	Context cxt;

	std::vector<Expr*> a = std::vector<Expr*>();

	//Bool Expression Test
	a.push_back(new And_expr(new Bool_expr(true), new Xor_expr(new Not_expr(new Bool_expr(true), cxt), new Bool_expr(false), cxt), cxt));
	//a.push_back(new And_expr(new Bool_expr(true), new Xor_expr(new Not_expr(new Int_expr(20), cxt), new Bool_expr(false), cxt), cxt)); //assert

	//If Else Expression Test
	a.push_back(new If_else_expr(new Bool_expr(true), new Int_expr(10), new Int_expr(-4), cxt));
	a.push_back(new If_else_expr(new Bool_expr(false), new Int_expr(10), new Int_expr(-4), cxt));
	a.push_back(new If_else_expr(new Bool_expr(true), new Bool_expr(true), new Bool_expr(false), cxt));
	a.push_back(new If_else_expr(new Bool_expr(false), new Bool_expr(true), new Bool_expr(false), cxt));
	//a.push_back(new If_else_expr(new Bool_expr(false), new Bool_expr(true), new Int_expr(10), cxt)); //assert

	//Int Expression Test
	a.push_back(new Int_expr(20));
	a.push_back(new Eql_expr(new Int_expr(20), new Int_expr(20), cxt));
	a.push_back(new Eql_expr(new Int_expr(10), new Int_expr(20), cxt));
	a.push_back(new Neq_expr(new Int_expr(20), new Int_expr(20), cxt));
	a.push_back(new Neq_expr(new Int_expr(10), new Int_expr(20), cxt));
	a.push_back(new Lt_expr(new Int_expr(20), new Int_expr(20), cxt));
	a.push_back(new Lt_expr(new Int_expr(10), new Int_expr(20), cxt));
	a.push_back(new Lte_expr(new Int_expr(20), new Int_expr(20), cxt));
	a.push_back(new Lte_expr(new Int_expr(10), new Int_expr(20), cxt));
	a.push_back(new Gt_expr(new Int_expr(20), new Int_expr(20), cxt));
	a.push_back(new Gt_expr(new Int_expr(10), new Int_expr(20), cxt));
	a.push_back(new Gte_expr(new Int_expr(20), new Int_expr(20), cxt));
	a.push_back(new Gte_expr(new Int_expr(10), new Int_expr(20), cxt));

	a.push_back(new Add_expr(new Int_expr(20), new Int_expr(20), cxt));
	a.push_back(new Add_expr(new Int_expr(10), new Int_expr(20), cxt));
	a.push_back(new Add_expr(new Int_expr(-5), new Int_expr(1), cxt));
	a.push_back(new Add_expr(new Int_expr(1), new Int_expr(-5), cxt));
	//a.push_back(new Add_expr(new Int_expr(INT_MAX), new Int_expr(1), cxt)); //assert

	a.push_back(new Sub_expr(new Int_expr(20), new Int_expr(20), cxt));
	a.push_back(new Sub_expr(new Int_expr(10), new Int_expr(20), cxt));
	a.push_back(new Sub_expr(new Int_expr(-5), new Int_expr(1), cxt));
	a.push_back(new Sub_expr(new Int_expr(1), new Int_expr(-5), cxt));
	//a.push_back(new Sub_expr(new Int_expr(INT_MIN), new Int_expr(1), cxt)); //assert

	a.push_back(new Mul_expr(new Int_expr(20), new Int_expr(20), cxt));
	a.push_back(new Mul_expr(new Int_expr(10), new Int_expr(20), cxt));
	a.push_back(new Mul_expr(new Int_expr(-5), new Int_expr(1), cxt));
	a.push_back(new Mul_expr(new Int_expr(1), new Int_expr(-5), cxt));
	//a.push_back(new Mul_expr(new Int_expr(INT_MAX), new Int_expr(INT_MIN), cxt)); //assert

	a.push_back(new Div_expr(new Int_expr(20), new Int_expr(20), cxt));
	a.push_back(new Div_expr(new Int_expr(10), new Int_expr(20), cxt));
	a.push_back(new Div_expr(new Int_expr(-5), new Int_expr(1), cxt));
	a.push_back(new Div_expr(new Int_expr(1), new Int_expr(-5), cxt));
	//a.push_back(new Div_expr(new Int_expr(1), new Int_expr(0), cxt)); //assert

	a.push_back(new Mod_expr(new Int_expr(20), new Int_expr(20), cxt));
	a.push_back(new Mod_expr(new Int_expr(10), new Int_expr(20), cxt));
	a.push_back(new Mod_expr(new Int_expr(-5), new Int_expr(1), cxt));
	a.push_back(new Mod_expr(new Int_expr(1), new Int_expr(-5), cxt));
	//a.push_back(new Mod_expr(new Int_expr(1), new Int_expr(0), cxt)); //assert

	a.push_back(new Neg_expr(new Int_expr(20), cxt));
	a.push_back(new Neg_expr(new Int_expr(10), cxt));
	a.push_back(new Neg_expr(new Int_expr(-5), cxt));
	a.push_back(new Neg_expr(new Int_expr(1), cxt));

	//Test all expressions in vector a.
	for(int i = 0; i < a.size(); ++i) {
		print(a.at(i));
		std::cout << "\n == ";
		if(a.at(i)->check(cxt) == &cxt.bool_type) {
			if(eval(a.at(i)))
				std::cout << "true";
			else
				std::cout << "false";
			std::cout << "\n\n\n";
		}
		else {
			std::cout << eval(a.at(i));
			std::cout << "\n\n\n";
		}
	}

	
	std::cout << "\n\nLEXER, type 'q' to quit\n\n";
	Lexer l;

	std::string rsp;
	//std::cin >> rsp;
	rsp = "0+1-2*3/4%5   (!true || false && (true)) ? 20 : -10    10 < 20 <=30 >= 1 == (50) #comment\n\n";
	std::cout << rsp;
	while(rsp != "q") {
		l = Lexer(rsp.c_str());
		while(!l.Eof()) {
			Token* t = l.next();
			std::cout << t->print();
			std::cout << "\n";
		}
		std::cin >> rsp;
	}

	return 0;
}
