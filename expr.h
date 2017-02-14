#ifndef EXPR_H
#define EXPR_H

#include <cassert>
#include "visitor.h"
#include "type.h"

class Expr {
public:
	virtual ~Expr() { }
	virtual Type* check(Context&) { return NULL; }
	virtual void accept(Visitor&) = 0;
};

#endif