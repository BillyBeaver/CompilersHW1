#ifndef VISITOR_H
#define VISITOR_H

class Bool_expr;
class And_expr;
class Or_expr;
class Not_expr;
class Xor_expr;
class Int_expr;
class If_else_expr;
class Eql_expr;
class Lt_expr;
class Lte_expr;
class Gt_expr;
class Gte_expr;
class Neq_expr;
class Add_expr;
class Sub_expr;
class Mul_expr;
class Div_expr;
class Mod_expr;
class Neg_expr;

class Visitor {
public:
	virtual void visit(Bool_expr*) { }
	virtual void visit(And_expr*) { }
	virtual void visit(Or_expr*) { }
	virtual void visit(Not_expr*) { }
	virtual void visit(Xor_expr*) { }

	virtual void visit(If_else_expr*) { }
	virtual void visit(Eql_expr*) { }
	virtual void visit(Neq_expr*) { }

	virtual void visit(Int_expr*) { }
	virtual void visit(Lt_expr*) { }
	virtual void visit(Lte_expr*) { }
	virtual void visit(Gt_expr*) { }
	virtual void visit(Gte_expr*) { }

	virtual void visit(Add_expr*) { }
	virtual void visit(Sub_expr*) { }
	virtual void visit(Mul_expr*) { }
	virtual void visit(Div_expr*) { }
	virtual void visit(Mod_expr*) { }
	virtual void visit(Neg_expr*) { }
};

#endif