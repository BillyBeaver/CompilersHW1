#ifndef TYPE_H
#define TYPE_H

class Type {
public:
	virtual ~Type() { }
	virtual void accept(Visitor&) { }
};

class Bool_type : public Type { };
class Int_type : public Type { };

class Context {
public:
	Bool_type bool_type;
	Int_type int_type;
};

#endif